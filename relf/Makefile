CC = gcc
CFLAGS = -Wall -Wextra -Iio -Ielf
SOURCES = main.c io/io.c elf/elf_st.c
CLIBS = 

BUILD_DIR = ../build/

build_debug:
	$(CC) -g -o relf $(CFLAGS) $(SOURCES) 

build_standalone:
	$(CC) -o relf $(SOURCES) $(CFLAGS) $(CLIBS)
	
build_o:
	$(CC) -o $(BUILD_DIR)relf.o -c $(CFLAGS) main.c
	$(CC) -o $(BUILD_DIR)io.o -c $(CFLAGS) io/io.c
	$(CC) -o $(BUILD_DIR)elf_st.o -c $(CFLAGS) elf/elf_st.c

clean:
	rm ./relf