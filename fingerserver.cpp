#include "connectionMgr.h"

using namespace std;

int main(int argc, char *argv[])
{
	const int MAX_CONNECTIONS = 9;
	string port = "";
	if (argc < 2)
	{
		cerr << "expected port number" << endl;
		return -1;
	}
	port = string(argv[1]);
	ConnectionMgr mgr(MAX_CONNECTIONS);
	int listenSock = mgr.Listen(port);
	
	cerr << "server listening on port " << port << endl;
	
	while(true)
	{
		sockaddr_storage clientAddr;
		socklen_t clientAddrSize;
		int commSock = mgr.Accept(clientAddr, clientAddrSize);
		if (commSock == -1)
		{
			break;
		}
		
		if (!fork())
		{
			close(listenSock);

			cerr << "new client on port " << commSock << endl;
			cerr << "waiting to receive string from client..." << endl;
			string message = mgr.RecvString(commSock);
			cerr << "got string from client: " << message << endl;
		
			if (dup2(commSock, 1) < 0 || dup2(commSock, 2) < 0)
			{
				perror("dup2");
				break;
			}
			execl("/usr/bin/finger", "finger", message.c_str(), (char * )0);
			close(commSock);
			exit(-1);
		}
		close(commSock);
	}
	
	cerr << "shutting down server..." << endl;
	mgr.Disconnect();
	cerr << "server shut down" << endl;
	
	return 0;
}

