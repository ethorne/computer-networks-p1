#include "connectionMgr.h"

using namespace std;

struct CliArgs{
	string user;
	string host;
	unsigned short sock;
	
	string print()
	{
		string ret = "user:\t" + user +
					"\nhost:\t" + host +
					"\nsock:\t" + ConnectionMgr::NumToString<unsigned short>(sock);
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
	
	cerr << cliArgs->print() << endl;
	
	ConnectionMgr mgr(MAX_CONNECTIONS);
	mgr.Connect(cliArgs->host,
			ConnectionMgr::NumToString<unsigned short>(cliArgs->sock));
	
	if (mgr.CheckConnected())
	{
		cerr << "Successfully connected!" << endl;
	}
	else
	{
		cerr << "Failed to connect!" << endl;
		return -1;
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
	
	return true;
}


