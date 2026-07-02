#include "elf_st.h"

void read_header(ElfHeader *elf_header, char *buffer)
{
  memcpy(&elf_header->identity, buffer + IDENT, 16);

  elf_header->type = read_u16(buffer, TYPE);
  elf_header->machine = read_u16(buffer, MACHINE);
  elf_header->h_size = read_u16(buffer, H_SIZE);
  elf_header->ph_table_size = read_u16(buffer, PH_TABLE_SIZE);
  elf_header->ph_num = read_u16(buffer, PH_NUM);
  elf_header->sh_table_size = read_u16(buffer, SH_TABLE_SIZE);
  elf_header->sh_num = read_u16(buffer, SH_NUM);
  elf_header->sh_table_index = read_u16(buffer, SH_TABLE_INDEX);

  elf_header->version = read_u32(buffer, VERSION);
  elf_header->flags = read_u32(buffer, FLAGS);

  elf_header->entry = read_u64(buffer, ENTRY);
  elf_header->ph_table = read_u64(buffer, PH_TABLE);
  elf_header->sh_table = read_u64(buffer, SH_TABLE);
}

uint16_t read_u16(char *buffer, ElfOffset offset)
{
  uint16_t value;
  memcpy(&value, buffer + offset, sizeof(value));
  return value;
}

uint32_t read_u32(char *buffer, ElfOffset offset)
{
  uint32_t value;
  memcpy(&value, buffer + offset, sizeof(value));
  return value;
}

uint64_t read_u64(char *buffer, ElfOffset offset)
{
  uint64_t value;
  memcpy(&value, buffer + offset, sizeof(value));
  return value;
}

void print_magic(unsigned char ident[], size_t start, size_t end, const char *field)
{
  printf("\t%s:\t ", field);
  for (size_t i = start; i < end; i++)
  {
    printf("%02x ", ident[i]);
  }
  printf("\n");
}

void print_class(unsigned char ident[], const char *field)
{
  printf("\t%s:\t ", field);
  printf("%s ", ident[0x04] == BIT32 ? "ELF32" : "ELF64");
  printf("\n");
}
