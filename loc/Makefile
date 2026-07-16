CC = gcc
CFLAGS = -Wall -Wextra -Iwalker -Iproj
CLIBS = 
SOURCES = main.c walker/walker.c proj/proj.c

BUILD_DIR = ../build/

build_o:
	$(CC) -o $(BUILD_DIR)loc.o -c $(CFLAGS) main.c
	$(CC) -o $(BUILD_DIR)walker.o -c $(CFLAGS) walker/walker.c
	$(CC) -o $(BUILD_DIR)proj.o -c $(CFLAGS) proj/proj.c
