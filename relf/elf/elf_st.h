#ifndef ELFST_H
#define ELFST_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define MAGIC_SIZE 16

typedef enum
{
  BIT32 = 0x01,
  BIT64 = 0x02
} Format;

typedef enum
{
  L_ENDIAN = 0x01,
  B_ENDIAN = 0x02
} Endian;

typedef enum
{
  SYSTEM_V = 0x00,
  HP_UX = 0x01,
  NETBSD = 0x02,
  LINUX = 0x03,
  GNU_HURD = 0x04,
  SOLARIS = 0x06,
  AIX = 0x07,
  IRIX = 0x08,
  FREEBSD = 0x09,
  TRU64 = 0x0A,
  NOVELL_MODESTO = 0x0B,
  OPENBSD = 0x0C,
  OPENVMS = 0x0D,
  NONSTOP_KERNEL = 0x0E,
  AROS = 0x0F,
  FENIX_OS = 0x10,
  NUXI = 0x11,
  OPEN_VOS = 0x12
} OSABI;

typedef enum
{
  IDENT = 0x00,
  TYPE = 0x10,
  MACHINE = 0x12,
  VERSION = 0x14,
  ENTRY = 0x18,
  PH_TABLE = 0x20,
  SH_TABLE = 0x28,
  FLAGS = 0x30,
  H_SIZE = 0x34,
  PH_TABLE_SIZE = 0x36,
  PH_NUM = 0x38,
  SH_TABLE_SIZE = 0x3A,
  SH_NUM = 0x3C,
  SH_TABLE_INDEX = 0x3E,
  END = 0x40
} ElfOffset;

typedef struct ElfHeader
{
  unsigned char identity[MAGIC_SIZE];
  uint16_t type;
  uint16_t machine;
  uint32_t version;
  uint64_t entry;
  uint64_t ph_table;
  uint64_t sh_table;
  uint32_t flags;
  uint16_t h_size;
  uint16_t ph_table_size;
  uint16_t ph_num;
  uint16_t sh_table_size;
  uint16_t sh_num;
  uint16_t sh_table_index;
} ElfHeader;

void read_header(ElfHeader *elf_header, char *buffer);
uint16_t read_u16(char *buffer, ElfOffset offset);
uint32_t read_u32(char *buffer, ElfOffset offset);
uint64_t read_u64(char *buffer, ElfOffset offset);
void print_magic(unsigned char ident[], size_t start, size_t end, const char *field);
void print_class(unsigned char ident[], const char* field);

#endif