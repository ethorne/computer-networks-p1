#ifndef CONNECTION_MGR_H
#define CONNECTION_MGR_H

#include <sstream>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

using namespace std;

class ConnectionMgr
{
	public:
		ConnectionMgr(int maximumConnections);
		~ConnectionMgr();
		int Connect(string host, string port);
		void Disconnect();
	
		void Listen(string port);
		int Accept(sockaddr_storage &clientAddr, socklen_t &addrSize);

		string RecvString(int port);
		bool SendString(int port, string data);
		
		template <typename N>
		static string NumToString(N num)
		{
			ostringstream cnvrt;
			cnvrt << num;
			return cnvrt.str();
		}
		static int StringToInt(string str);		
		
		bool CheckConnected();
		bool CheckListening();

	private:
		bool isConnected;
		bool isListening;
		int sock;
		int maxPending;
		
		addrinfo hints;
		addrinfo *serverInfo;
		sockaddr_in *socketInfo;
};
#endif

