CC = gcc
CFLAGS = -Wall -Wextra -Iio
SOURCES = main.c io/io.c
CLIBS = 

build_debug:
	$(CC) -g -o httpserv $(CFLAGS) $(SOURCES) 

build_standalone:
	$(CC) -o httpserv $(SOURCES) $(CFLAGS) $(CLIBS)

clean:
	rm ./httpserv