#include "connectionMgr.h"

ConnectionMgr::ConnectionMgr(int maximumConnections)
{
	memset(&(this->hints), 0, sizeof this->hints);
	this->hints.ai_family = AF_UNSPEC;		// ipv4 or ipv6
	this->hints.ai_socktype = SOCK_STREAM;	// TCP stream sockets

	this->sock = -1;
	this->maxPending = maximumConnections;
	this->serverInfo = NULL;
	this->socketInfo = NULL;
}

int ConnectionMgr::Connect(string host, string port)
{
	// TODO : allow to connect if already isConnected?
	this->isConnected = false;

	int status = getaddrinfo(host.c_str(), port.c_str(),
								&(this->hints), &(this->serverInfo));
	if (status != 0)
	{
		this->isConnected = false;
		cerr << "[cxn mgr] ERROR getting address info for " << host << endl;
		fprintf(stderr, "\tgetaddrinfo:\t%s\n", gai_strerror(status));
		return -1;
	}
	
	addrinfo *p;
	for (p = this->serverInfo; p != NULL; p = p->ai_next)
	{
		if ((this->sock = socket(p->ai_family, 
						p->ai_socktype, p->ai_protocol)) == -1)
		{
			perror("[cxn mgr] socket");
			continue;
		}

		if (connect(this->sock, p->ai_addr, p->ai_addrlen) == -1)
		{
			perror("[cxn mgr] connect");
			close(this->sock);
			continue;
		}
		this->isConnected = true;
		break;
	}
	return this->sock;
}


void ConnectionMgr::Disconnect()
{
	freeaddrinfo(serverInfo);
	close(this->sock);
	this->isConnected = false;
	this->isListening = false;
	if (this->socketInfo != NULL)
	{
		delete this->socketInfo;
	}
}

int ConnectionMgr::Listen(string port)
{
	this->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->sock < 0)
	{
		this->isListening = false;
		return -1;
	}
	
	if (this->socketInfo != NULL)
	{
		delete this->socketInfo;
	}
	this->socketInfo = new sockaddr_in;
	this->socketInfo->sin_family = AF_INET;
	this->socketInfo->sin_addr.s_addr = htonl(INADDR_ANY);
	this->socketInfo->sin_port = htons((unsigned short)
										ConnectionMgr::StringToInt(port));
	int status = bind(this->sock, (sockaddr *) this->socketInfo, 
						sizeof *(this->socketInfo));	
	if (status < 0)
	{
		this->isListening = false;
		return -1;
	}
	status = listen(this->sock, this->maxPending);
	this->isListening = status >= 0;
	return this->sock;
}

int ConnectionMgr::Accept(sockaddr_storage &clientAddr, socklen_t &addrSize)
{
	if (!this->isListening)
	{
		cerr << "[cxn mgr] user trid to Accept() without calling Listen() "
			 << "- doing nothing" << endl;
		return -1;
	}
	addrSize = sizeof clientAddr;
	return accept(this->sock, (sockaddr *) &clientAddr, &addrSize);
}

string ConnectionMgr::RecvString(int port)
{
	const int MAXBUFF = 1000;
	char buffer[MAXBUFF + 1];
	for(int i = 0; i < MAXBUFF + 1; i++)
	{
		buffer[i] = '\0';
	}
	char *bufferPtr = buffer;
	int bytesRead = 0;
	while ((bytesRead = recv(port, (void*) bufferPtr, MAXBUFF, 0)) > 0)
	{
		if (*(bufferPtr + bytesRead) == '\0')
		{
			break;
		}
		bufferPtr += bytesRead;
	}
	return string(bufferPtr);
}

bool ConnectionMgr::SendString(int port, string data)
{
	data += '\0'; // add null terminating character
	int bytesSent = send(port, (void*) data.c_str(), data.length(), 0);
	bool ret = bytesSent == -1 || bytesSent == (int) data.length();
	if (!ret)
	{
		perror("[cxn mgr] Send String");
	}
	return ret;
}

int ConnectionMgr::StringToInt(string str)
{
	return atoi(str.c_str());
}

bool ConnectionMgr::CheckConnected()
{
	return this->isConnected;
}

bool ConnectionMgr::CheckListening()
{
	return this->isListening;
}

ConnectionMgr::~ConnectionMgr()
{
	if (this->isConnected)
		this->Disconnect();
}
