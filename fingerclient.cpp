#include<iostream>
#include "core.h"
#include<cstring>
#include<stdlib.h>

using namespace std;

struct CliArgs{
	string user;
	string addr;
	string port;
	
	string print()
	{
		string ret = "user:\t" + user + "\naddr:\t" + addr + "\nport:\t" + port;
		return ret;
	}
};

void getCliArgs(int argc, char *argv[], CliArgs *args);

int main(int argc, char *argv[])
{
	CliArgs *cliArgs = new CliArgs;
	getCliArgs(argc, argv, cliArgs);
	if (cliArgs == NULL)
	{
		cerr << "insufficient command line arguments" << endl;
		cerr << "expected username@hostname.com:<portNumber>" << endl;
		return -1;	
	}

	cerr << "recieved arguments..." << endl;
	cerr << cliArgs->print() << endl;

	delete cliArgs;
	return 0;
}

void getCliArgs(int argc, char *argv[], CliArgs *args)
{
	if (argc < 2)
	{
		args = NULL;
		return;
	}
	string raw = string(argv[1]);

	size_t atPos = raw.find('@');
	size_t colonPos = raw.find(':');
	
	if (atPos == string::npos || colonPos == string::npos)
	{
		args = NULL;
		return;
	}
	
	args->user = raw.substr(0, atPos);
	args->addr = raw.substr(atPos + 1, colonPos - atPos -  1);
	args->port = raw.substr(colonPos + 1, raw.length() - colonPos);
}

