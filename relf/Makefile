CC = gcc
CFLAGS = -Wall -Wextra -Iio -Ielf -Iforeign
SOURCES = main.c io/io.c elf/elf_st.c
CLIBS = 

GHC = ghc
GHC_FLAGS = --make -dynamic -shared -fPIC
GHC_SOURCES = foreign/ELFF.hs

GHC_INC = -I/usr/lib/ghc/lib/x86_64-linux-ghc-9.4.7/rts-1.0.2/include

BUILD_DIR = ../build/

build_o:
	$(GHC) $(GHC_FLAGS) $(GHC_SOURCES) -o $(BUILD_DIR)libhs.so
	$(CC) -o $(BUILD_DIR)relf.o -c $(CFLAGS) $(GHC_INC) main.c
	$(CC) -o $(BUILD_DIR)io.o -c $(CFLAGS) io/io.c
	$(CC) -o $(BUILD_DIR)elf_st.o -c $(CFLAGS) elf/elf_st.c
