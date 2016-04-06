CFLAGS= -ansi -Wall -Werror -pedantic -Wno-write-strings -Wno-return-local-addr

all: fingerclient fingerserver

fingerclient: fingerclient.cpp core
	g++ $(CFLAGS) fingerclient.cpp core -o fingerclient

fingerserver: fingerserver.cpp core
	g++ $(CFLAGS) fingerserver.cpp core -o fingerserver

core: core.h core.cpp
	g++ $(CFLAGS) -c core.cpp -o core

clean:
	rm -f *.o
	rm -f core
	rm -f fingerserver
	rm -f fingerclient

