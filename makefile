CFLAGS= -ansi -Wall -Werror -pedantic

all:
	make fingerclient
	make fingerserver

fingerclient: fingerclient.cpp core.o
	g++ $(CFLAGS) fingerclient.cpp core.cpp -o fingerclient

fingerserver: fingerserver.cpp core.o
	g++ $(CFLAGS) fingerserver.cpp core.cpp -o fingerserver

core.o: core.cpp
	g++ $(CFLAGS) -c core.cpp -o core.o

clean:
	rm -f *.o
	rm -f fingerserver
	rm -f fingerclient

