CC = gcc
CFLAGS = -Wall -Wextra -Iio -Ielf -Iforeign
SOURCES = main.c io/io.c elf/elf_st.c
CLIBS = 

GHC = ghc
GHC_FLAGS = --make -dynamic -shared -fPIC
GHC_SOURCES = foreign/ELFF.hs

GHC_ROOT := /usr/lib/ghc/lib
GHC_INC_PATH := $(dir $(firstword $(wildcard $(GHC_ROOT)/x86_64-linux-ghc*/rts*/)))

BUILD_DIR = ../build/

build_o:
	$(GHC) $(GHC_FLAGS) $(GHC_SOURCES) -o $(BUILD_DIR)libhs.so
	$(CC) -o $(BUILD_DIR)relf.o -c $(CFLAGS) -I$(GHC_INC_PATH)include main.c
	$(CC) -o $(BUILD_DIR)io.o -c $(CFLAGS) io/io.c
	$(CC) -o $(BUILD_DIR)elf_st.o -c $(CFLAGS) elf/elf_st.c
