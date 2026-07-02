#include "io.h"
#include "elf_st.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Insufficient Arguments!\n");
    exit(EXIT_FAILURE);
  }
  int fd = load_file(argv[1], O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
  char *buffer = read_file(&fd);
  close_fd(&fd);

  ElfHeader elf_header = {0};
  read_header(&elf_header, buffer);

  printf("ELF Header: \n");

  print_magic(elf_header.identity, IDENT, 16, "MAGIC");
  print_class(elf_header.identity, "CLASS");

  free(buffer);
  return 0;
}