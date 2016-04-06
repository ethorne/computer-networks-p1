CFLAGS= -ansi -Wall -Werror -pedantic

all:
	make fingerclient
	make fingerserver

fingerclient:
	g++ $(CFLAGS) fingerclient.cpp core.cpp -o fingerclient

fingerserver:
	g++ $(CFLAGS) fingerserver.cpp core.cpp -o fingerserver

core.o:
	g++ $(CFLAGS) -c core.cpp -o core.o

clean:
	rm -f *.o
	rm -f fingerserver
	rm -f fingerclient

