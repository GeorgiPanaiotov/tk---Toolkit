#include "io.h"
#include "elf_st.h"

int relf_main(int argc, char *argv[])
{
  if (argc < 2 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
  {
    printf("Usage: %s <target_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  int fd = r_load_file(argv[1], O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
  char *buffer = read_file(&fd);
  close_fd(&fd);

  ElfHeader elf_header = {0};
  read_header(&elf_header, buffer);

  printf("\e[1m");
  printf("\t ELF Header: \n\n");
  printf("\e[0m");

  print_magic(elf_header.identity, IDENT, 16, "MAGIC");
  print_class(elf_header.identity, "CLASS", EI_CLASS);
  print_data(elf_header.identity, "DATA", EI_DATA);
  print_ident_version("VERSION");
  print_osabi(elf_header.identity, "OS/ABI", EI_OSABI);
  print_abiversion(elf_header.identity, "ABI VERSION", EI_ABIVERSION);
  print_object_type("TYPE", elf_header.type);
  print_machine("MACHINE", elf_header.machine);
  print_version("VERSION", elf_header.version);
  print_entry("ENTRY ADDRESS", elf_header.entry);

  free(buffer);
  return 0;
}