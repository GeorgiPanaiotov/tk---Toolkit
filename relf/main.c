#include "io.h"
#include "elf_st.h"
#include "ELFF_stub.h"

int relf_main(int argc, char *argv[])
{
  if (argc < 2 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
  {
    printf("Usage: %s <target_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  hs_init(&argc, &argv);
  int fd = r_load_file(argv[1], O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
  char *buffer = read_file(&fd);
  off_t file_size = r_get_file_size(&fd);
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
  hs_fmt_osabi((unsigned char *)buffer, file_size);
  print_abiversion(elf_header.identity, "ABI VERSION", EI_ABIVERSION);
  hs_fmt_type((unsigned char *)buffer, file_size);
  print_machine("MACHINE", elf_header.machine);
  print_version("VERSION", elf_header.version);
  print_entry("ENTRY ADDRESS", elf_header.entry);

  hs_exit();
  free(buffer);
  return 0;
}