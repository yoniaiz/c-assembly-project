assembly: main.o
	gcc -g -Wall -pedantic -ansi main.o -o assembly -lm
main.o: main.c header.h
	gcc -c -Wall -pedantic -ansi main.c -o main.o