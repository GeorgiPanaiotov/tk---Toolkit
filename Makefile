ASSEMBLER = fasm
ASM_SOURCES = tk.asm

BUILD_DIR = build/

GHC_LIB_PATH = /usr/lib/ghc/lib/x86_64-linux-ghc-9.4.7

MU_OFILES = $(BUILD_DIR)mu.o $(BUILD_DIR)collector.o $(BUILD_DIR)proj_stat.o
LOC_OFILES = $(BUILD_DIR)loc.o $(BUILD_DIR)proj.o $(BUILD_DIR)walker.o
RELF_OFILES = $(BUILD_DIR)relf.o $(BUILD_DIR)io.o $(BUILD_DIR)elf_st.o
TM_OFILES = $(BUILD_DIR)tm.o
PSM_OFILES = $(BUILD_DIR)psm.o

OBJ_FILES = $(BUILD_DIR)tkit.o $(MU_OFILES) $(LOC_OFILES) $(RELF_OFILES) $(TM_OFILES) $(PSM_OFILES)

CC = gcc

build_and_link:
	cd loc && make build_o
	cd mu && make build_o
	cd relf && make build_o
	cd tm && make build_o
	cd psm && make build_o
	$(ASSEMBLER) $(ASM_SOURCES) $(BUILD_DIR)tkit.o
	$(CC) \
    $(OBJ_FILES) \
    $(BUILD_DIR)libhs.so \
    -L$(GHC_LIB_PATH) \
    -l:libHSrts-1.0.2-ghc9.4.7.so \
    -l:libHSbase-4.17.2.0-ghc9.4.7.so \
    -l:libHSghc-bignum-1.3-ghc9.4.7.so \
    -l:libHSghc-prim-0.9.1-ghc9.4.7.so \
    -lgmp \
    -lm \
    -Wl,-rpath,'$$ORIGIN/' \
    -Wl,-rpath,$(GHC_LIB_PATH) \
		-no-pie \
    -o $(BUILD_DIR)tk

clean:
	rm $(OBJ_FILES) $(BUILD_DIR)tk