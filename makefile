assembly: ofiles/main.o ofiles/helpers.o
	gcc -g -Wall -pedantic -ansi ofiles/main.o ofiles/helpers.o -o assembly -lm
ofiles/main.o: main.c header.h helpers.c
	gcc -c -Wall -pedantic -ansi main.c -o ofiles/main.o
ofiles/helpers.o: helpers.c header.h
	gcc -c -Wall -pedantic -ansi helpers.c -o ofiles/helpers.o