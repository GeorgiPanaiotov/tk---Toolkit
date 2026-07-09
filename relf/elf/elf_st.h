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

typedef enum
{
  EI_MAG0 = 0x00,
  EI_MAG1 = 0x01,
  EI_MAG2 = 0x02,
  EI_MAG3 = 0x03,
  EI_CLASS = 0x04,
  EI_DATA = 0x05,
  EI_VERSION = 0x06,
  EI_OSABI = 0x07,
  EI_ABIVERSION = 0x08,
  EI_PAD = 0x09
} IdentOffset;

typedef enum
{
  ET_NONE = 0x00,
  ET_REL = 0x01,
  ET_EXEC = 0x02,
  ET_DYN = 0x03,
  ET_CORE = 0x04,
} ObjectType;

typedef enum
{
  MT_NONE = 0x00,
  MT_ATT = 0x01,
  MT_SPARC = 0x02,
  MT_X86 = 0x03,
  MT_MOTOROLA68000 = 0x04,
  MT_MOTOROLA88000 = 0x05,
  MT_INTELMCU = 0x06,
  MT_INTEL80860 = 0x07,
  MT_MIPS = 0x08,
  MT_IBMSYSTEM370 = 0x09,
  MT_MIPSRS3000LE = 0x0A,
  MT_RESERVED = 0x0B,
  MT_HP_PA_RISC = 0x0F,
  MT_INTEL80960 = 0x13,
  MT_POWERPC = 0x14,
  MT_POWERPC64 = 0x15,
  MT_S390 = 0x16,
  MT_IBMSPU = 0x17,
  MT_RESERVED2 = 0x18,
  MT_NECV800 = 0x24,
  MT_FUJITSUFR20 = 0x25,
  MT_TRWRH32 = 0x26,
  MT_MOTOROLARCE = 0x27,
  MT_ARM = 0x28,
  MT_DIGITALALPHA = 0x29,
  MT_SUPERH = 0x2A,
  MT_SPARCV9 = 0x2B,
  MT_SIEMENSTRICORE_EMBEDDED = 0x2C,
  MT_ARGONAUTRISC = 0x2D,
  MT_HITACHIH8300 = 0x2E,
  MT_HITACHIH8300H = 0x2F,
  MT_HITACHIH8S = 0x30,
  MT_HITACHIH8500 = 0x31,
  MT_IA64 = 0x32,
  MT_STANFORDMIPSX = 0x33,
  MT_MOTOROLACOLDFIRE = 0x34,
  MT_MOTOROLAM68HC12 = 0x35,
  MT_FUJITSUMMA = 0x36,
  MT_SIEMENSPCP = 0x37,
  MT_SONYNCPURISC_EMBEDDED = 0x38,
  MT_DENSONDR1 = 0x39,
  MT_MOTOROLASTAR = 0x3A,
  MT_TOYOTAME16 = 0x3B,
  MT_STMICROELECTRONICSST100 = 0x3C,
  MT_ADVANCEDLOGICCORPTINYJ = 0x3D,
  MT_AMDX8664 = 0x3E,
  MT_SONYDSP = 0x3F,
  MT_DIGITALPDP10 = 0x40,
  MT_DIGITALPDP11 = 0x41,
  MT_SIENEBSFX66 = 0x42,
  MT_STMICROELECTRONICSST9 = 0x43,
  MT_STMICROELECTRONICSST7 = 0x44,
  MT_MOTOROLAMC68HC16 = 0x45,
  MT_MOTOROLAMC68HC11 = 0x46,
  MT_MOTOROLAMC68HC08 = 0x47,
  MT_MOTOROLAMC68HC05 = 0x48,
  MT_SILICONGRAPHICSSVX = 0x49,
  MT_STMICROELECTRONICSST198 = 0x4A,
  MT_DIGITALVAX = 0x4B,
  MT_AXIS32_EMBEDDED = 0x4C,
  MT_INFININEON32_EMBEDDED = 0x4D,
  MT_ELEMENT64DSP = 0x4E,
  MT_LSI16DSP = 0x4F,
  MT_TMS320C6000 = 0x8C,
  MT_MCSTELBRUS = 0xAF,
  MT_ARM64 = 0xB7,
  MT_ZILOGZ80 = 0xDC,
  MT_RISCV = 0xF3,
  MT_BPF = 0xF7,
  MT_WDC = 0x101,
  MT_LOONGARCH = 0x102
} MachineType;

void read_header(ElfHeader *elf_header, char *buffer);
uint16_t read_u16(char *buffer, ElfOffset offset);
uint32_t read_u32(char *buffer, ElfOffset offset);
uint64_t read_u64(char *buffer, ElfOffset offset);
void print_magic(unsigned char ident[], size_t start, size_t end, const char *field);
void print_class(unsigned char ident[], const char *field, IdentOffset ident_offset);
void print_data(unsigned char ident[], const char *field, IdentOffset ident_offset);
void print_ident_version(const char *field);
void print_osabi(unsigned char ident[], const char *field, IdentOffset ident_offset);
void print_abiversion(unsigned char ident[], const char *field, IdentOffset ident_offset);
void print_object_type(const char *field, uint16_t type);
void print_machine(const char *field, uint16_t type);
void print_version(const char *field, uint32_t version);
void print_entry(const char *field, uint64_t address);
char *get_osabi(unsigned char c);
char *get_obj_type(uint16_t type);
char *get_machine_type(uint16_t machine);

#endif