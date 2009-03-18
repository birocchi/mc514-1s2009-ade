main: main.c matriz.o interface.o threads.o
	gcc -Wall -pthread -g matriz.o interface.o threads.o main.c -o main

matriz.o: matriz.h matriz.c
	gcc -Wall -pthread -g -c matriz.c 

interface.o: interface.h interface.c
	gcc -Wall -pthread -g -c interface.c

threads.o: threads.h threads.c
	gcc -Wall -pthread -g -c threads.c

clean:
	rm -f *.o main
	clear
