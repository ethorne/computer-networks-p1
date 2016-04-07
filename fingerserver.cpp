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
	mgr.Listen(port);
	while(true)
	{
		sockaddr_storage clientAddr;
		socklen_t clientAddrSize;
		int commSock = mgr.Accept(clientAddr, clientAddrSize);
		if (commSock == -1)
		{
			break;
		}
		cerr << "got one! new client on port " << commSock << endl;
		break;
	}
	mgr.Disconnect();
	return 0;
}

