main: Rollercoaster.c
	gcc -Wall -pthread -g Rollercoaster.c -o Rollercoaster

clean:
	rm -f Rollercoaster
	rm -f *~
	rm -f *.o
	clear

