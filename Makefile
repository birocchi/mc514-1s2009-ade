main: main.c matriz.o
	gcc -Wall -g matriz.o main.c -o main

matriz.o: matriz.h matriz.c
	gcc -Wall -g -c matriz.c 

clean:
	rm -f *.o main
	clear
