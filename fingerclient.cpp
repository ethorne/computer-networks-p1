#include "connectionMgr.h"

using namespace std;

struct CliArgs{
	string user;
	string host;
	unsigned short sock;
	string sockStr;
	
	string print()
	{
		string ret = "user:\t" + user +
					"\nhost:\t" + host +
					"\nsock:\t" + sockStr;
		return ret;
	}
};

bool getCliArgs(int argc, char *argv[], CliArgs *args);

int main(int argc, char *argv[])
{
	const int MAX_CONNECTIONS = 9;
	CliArgs *cliArgs = new CliArgs;
	if (!getCliArgs(argc, argv, cliArgs))
	{
		cerr << "insufficient command line arguments" << endl;
		cerr << "expected username@hostname<port>" << endl;
		return -1;	
	}
	
	ConnectionMgr mgr(MAX_CONNECTIONS);
	int sockfd = mgr.Connect(cliArgs->host, cliArgs->sockStr);
	
	if (!mgr.CheckConnected())
	{
		cerr << "Failed to connect!" << endl;
		return -1;
	}
	
	if (mgr.SendString(sockfd, cliArgs->user))
	{
		cerr << mgr.RecvString(sockfd) << endl;
	}
	else
	{
		cerr << "failed to send command to host on port " << sockfd << endl;
	}
	mgr.Disconnect();
	delete cliArgs;
	return 0;
}

bool getCliArgs(int argc, char *argv[], CliArgs *args)
{
	if (argc < 2)
	{
		args = NULL;
		return false;
	}
	string raw = string(argv[1]);

	size_t atPos = raw.find('@');
	size_t colonPos = raw.find(':');
	
	if (atPos == string::npos || colonPos == string::npos)
	{
		args = NULL;
		return false;
	}
	
	args->user = raw.substr(0, atPos);
	args->host = raw.substr(atPos + 1, colonPos - atPos -  1);
	string sockStr = raw.substr(colonPos + 1, raw.length() - colonPos);
	args->sock = atoi(sockStr.c_str());
	args->sockStr = sockStr;	
	return true;
}


