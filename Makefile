main: camp.c
	gcc -Wall -pthread -g camp.c -o camp
	gcc -Wall -pthread -g camperro.c -o camperro

clean:
	rm -f *.o main
	clear
