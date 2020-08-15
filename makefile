assembly: ofiles/main.o ofiles/helpers.o ofiles/file_handler.o ofiles/messages.o ofiles/initializers.o ofiles/assembly_compiler.o ofiles/first_loop.o ofiles/second_loop.o ofiles/assembly_helpers.o
	gcc -g -Wall -pedantic -ansi ofiles/main.o ofiles/helpers.o ofiles/file_handler.o ofiles/initializers.o ofiles/messages.o ofiles/assembly_compiler.o ofiles/first_loop.o ofiles/second_loop.o ofiles/assembly_helpers.o -o assembly -lm
ofiles/main.o: src/main.c src/header.h src/helpers.c src/assembly_compiler/header.h
	gcc -c -Wall -pedantic -ansi src/main.c -o ofiles/main.o
ofiles/file_handler.o: src/file_handler.c src/header.h
	gcc -c -Wall -pedantic -ansi src/file_handler.c -o ofiles/file_handler.o
ofiles/helpers.o: src/helpers.c src/header.h
	gcc -c -Wall -pedantic -ansi src/helpers.c -o ofiles/helpers.o
ofiles/assembly_compiler.o: src/assembly_compiler/assembly_compiler.c src/header.h src/assembly_compiler/header.h
	gcc -c -Wall -pedantic -ansi src/assembly_compiler/assembly_compiler.c -o ofiles/assembly_compiler.o
ofiles/first_loop.o: src/assembly_compiler/first_loop.c src/header.h src/assembly_compiler/header.h
	gcc -c -Wall -pedantic -ansi src/assembly_compiler/first_loop.c -o ofiles/first_loop.o
ofiles/second_loop.o: src/assembly_compiler/second_loop.c src/header.h src/assembly_compiler/header.h
	gcc -c -Wall -pedantic -ansi src/assembly_compiler/second_loop.c -o ofiles/second_loop.o
ofiles/assembly_helpers.o: src/assembly_compiler/assembly_helpers.c src/header.h src/assembly_compiler/header.h
	gcc -c -Wall -pedantic -ansi src/assembly_compiler/assembly_helpers.c -o ofiles/assembly_helpers.o
ofiles/messages.o: src/messages.c src/header.h
	gcc -c -Wall -pedantic -ansi src/messages.c -o ofiles/messages.o
ofiles/initializers.o: src/initializers.c src/header.h
	gcc -c -Wall -pedantic -ansi src/initializers.c -o ofiles/initializers.o