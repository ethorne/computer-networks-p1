#ifndef CORE_H
#define CORE_H

using namespace std;

class Core{
	public:
		Core();
		~Core();
		static void RecvString(int port, char* data);
		static void SendString(int port, char* data);
};
#endif

