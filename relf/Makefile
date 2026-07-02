CC = gcc
CFLAGS = -Wall -Wextra -Iio -Ielf
SOURCES = main.c io/io.c elf/elf_st.c
CLIBS = 

build_debug:
	$(CC) -g -o relf $(CFLAGS) $(SOURCES) 

build_standalone:
	$(CC) -o relf $(SOURCES) $(CFLAGS) $(CLIBS)

clean:
	rm ./relf