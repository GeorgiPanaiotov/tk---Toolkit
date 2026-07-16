CC = gcc
CFLAGS = -Wall -Wextra -Icollector -Istat
SOURCES = main.c collector/collector.c stat/proj_stat.c
CLIBS = 

BUILD_DIR = ../build/

build_o:
	$(CC) -o $(BUILD_DIR)mu.o -c $(CFLAGS) main.c
	$(CC) -o $(BUILD_DIR)collector.o -c $(CFLAGS) collector/collector.c
	$(CC) -o $(BUILD_DIR)proj_stat.o -c $(CFLAGS) stat/proj_stat.c
