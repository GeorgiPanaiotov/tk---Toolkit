CC = gcc
CFLAGS = -Wall -Wextra -Ifile_handler -Iparser
SOURCES = main.c file_handler/file_handler.c parser/token.c parser/parser.c parser/ast.c
CLIBS = 

build_debug:
	$(CC) -g -o mdc $(CFLAGS) $(SOURCES) 

build_standalone:
	$(CC) -o mdc $(CFLAGS) $(SOURCES)

clean:
	rm ./mdc