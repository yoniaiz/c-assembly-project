assembly: ofiles/main.o ofiles/helpers.o ofiles/file_handler.o ofiles/messages.o ofiles/initializers.o
	gcc -g -Wall -pedantic -ansi ofiles/main.o ofiles/helpers.o ofiles/file_handler.o ofiles/initializers.o ofiles/messages.o -o assembly -lm
ofiles/main.o: main.c header.h helpers.c
	gcc -c -Wall -pedantic -ansi main.c -o ofiles/main.o
ofiles/file_handler.o: file_handler.c header.h
	gcc -c -Wall -pedantic -ansi file_handler.c -o ofiles/file_handler.o
ofiles/helpers.o: helpers.c header.h
	gcc -c -Wall -pedantic -ansi helpers.c -o ofiles/helpers.o
ofiles/messages.o: messages.c header.h
	gcc -c -Wall -pedantic -ansi messages.c -o ofiles/messages.o
ofiles/initializers.o: initializers.c header.h
	gcc -c -Wall -pedantic -ansi initializers.c -o ofiles/initializers.o