main: camp.c
	gcc -Wall -pthread -g camp.c -o camp

clean:
	rm -f *.o main
	clear
