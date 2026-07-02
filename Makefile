ASSEMBLER = fasm
ASM_SOURCES = tk.asm

BUILD_DIR = build/

OBJ_FILES = $(BUILD_DIR)tkit.o $(BUILD_DIR)collector.o $(BUILD_DIR)loc.o $(BUILD_DIR)mu.o $(BUILD_DIR)proj_stat.o $(BUILD_DIR)proj.o $(BUILD_DIR)walker.o 

CC = gcc

build_and_link:
	cd loc/ && make build_o
	cd mu/ && make build_o
	$(ASSEMBLER) $(ASM_SOURCES) $(BUILD_DIR)tkit.o
	$(CC) $(OBJ_FILES) -o $(BUILD_DIR)tk