main: main.c matriz.o interface.o
	gcc -Wall -g matriz.o interface.o main.c -o main

matriz.o: matriz.h matriz.c
	gcc -Wall -g -c matriz.c 

interface.o: interface.h interface.c
	gcc -Wall -g -c interface.c

clean:
	rm -f *.o main
	clear
