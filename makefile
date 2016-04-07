CFLAGS= -ansi -Wall -Werror -pedantic -Wno-write-strings -Wno-return-local-addr

all: fingerclient fingerserver 

fingerclient: fingerclient.cpp connectionMgr
	g++ $(CFLAGS) fingerclient.cpp connectionMgr -o fingerclient

fingerserver: fingerserver.cpp connectionMgr
	g++ $(CFLAGS) fingerserver.cpp connectionMgr -o fingerserver

connectionMgr: connectionMgr.h connectionMgr.cpp
	g++ $(CFLAGS) -c connectionMgr.cpp -o connectionMgr

clean:
	rm -f *.o
	rm -f connectionMgr
	rm -f fingerserver
	rm -f fingerclient

