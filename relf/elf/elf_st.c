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
  printf("%-30s ", field);
  for (size_t i = start; i < end; i++)
  {
    printf("%02x ", ident[i]);
  }
  printf("\n");
}

void print_class(unsigned char ident[], const char *field, IdentOffset ident_offset)
{
  printf("%-30s ", field);
  printf("%s ", ident[ident_offset] == BIT32 ? "ELF32" : "ELF64");
  printf("\n");
}

void print_data(unsigned char ident[], const char *field, IdentOffset ident_offset)
{
  printf("%-30s ", field);
  printf("%s ", ident[ident_offset] == L_ENDIAN ? "Little Endian" : "Big Endian");
  printf("\n");
}

void print_ident_version(const char *field)
{
  printf("%-30s ", field);
  printf("%s ", "1 (current and original)");
  printf("\n");
}

void print_abiversion(unsigned char ident[], const char *field, IdentOffset ident_offset)
{
  printf("%-30s ", field);
  printf("%x ", ident[ident_offset]);
  printf("\n");
}

void print_machine(const char *field, uint16_t type)
{
  printf("%-30s ", field);
  printf("%s ", get_machine_type(type));
  printf("\n");
}

void print_version(const char *field, uint32_t version)
{
  printf("%-30s ", field);
  printf("0x%x ", version);
  printf("\n");
}

void print_entry(const char *field, uint64_t address)
{
  printf("%-30s ", field);
  printf("0x%08lx ", address);
  printf("\n");
}

char *get_machine_type(uint16_t machine)
{
  switch (machine)
  {
  case MT_NONE:
    return "None";
  case MT_ATT:
    return "AT&T";
  case MT_SPARC:
    return "Scalable Processor ARChitecture";
  case MT_X86:
    return "Intel x86";
  case MT_MOTOROLA68000:
    return "Motorola 68000";
  case MT_MOTOROLA88000:
    return "Motorola 88000";
  case MT_INTELMCU:
    return "Intel MCU";
  case MT_INTEL80860:
    return "Intel i860";
  case MT_MIPS:
    return "MIPS";
  case MT_IBMSYSTEM370:
    return "IBM S/370";
  case MT_MIPSRS3000LE:
    return "MIPS R3000 Little Endian";
  case MT_RESERVED:
    return "Reserved";
  case MT_RESERVED2:
    return "Reserved";
  case MT_HP_PA_RISC:
    return "Hewlett Packard PA-RISC";
  case MT_INTEL80960:
    return "Intel i960";
  case MT_POWERPC:
    return "PowerPC";
  case MT_POWERPC64:
    return "PowerPC 64-bit";
  case MT_S390:
    return "S390/S390x";
  case MT_IBMSPU:
    return "IBM SPU";
  case MT_NECV800:
    return "NEC V800";
  case MT_FUJITSUFR20:
    return "Fujitsu FR20";
  case MT_TRWRH32:
    return "TRW RH-32";
  case MT_MOTOROLARCE:
    return "Motorola RCE";
  case MT_ARM:
    return "ARM";
  case MT_DIGITALALPHA:
    return "Digital Alpha";
  case MT_SUPERH:
    return "Super H";
  case MT_SIEMENSTRICORE_EMBEDDED:
    return "Siemens TriCore Embedded";
  case MT_SPARCV9:
    return "SPARC v9";
  case MT_ARGONAUTRISC:
    return "Argonaut RISC Core";
  case MT_HITACHIH8300:
    return "Hitachi H8/300";
  case MT_HITACHIH8300H:
    return "Hitachi H8/300H";
  case MT_HITACHIH8S:
    return "Hitachi H8S";
  case MT_HITACHIH8500:
    return "Hitachi H8/500";
  case MT_IA64:
    return "IA-64";
  case MT_STANFORDMIPSX:
    return "Stanford MIPS-X";
  case MT_MOTOROLACOLDFIRE:
    return "Motorola ColdFire";
  case MT_MOTOROLAM68HC12:
    return "Motorola M68HC12";
  case MT_FUJITSUMMA:
    return "Fujitsu MMA Multimedia Accelerator";
  case MT_SIEMENSPCP:
    return "Siemens PCP";
  case MT_SONYNCPURISC_EMBEDDED:
    return "Sony nCPU embedded RISC processor";
  case MT_DENSONDR1:
    return "Denso NDR1 microprocessor";
  case MT_MOTOROLASTAR:
    return "Motorola Star*Core processor";
  case MT_TOYOTAME16:
    return "Toyota ME16 processor";
  case MT_STMICROELECTRONICSST100:
    return "STMicroelectronics ST100 processor";
  case MT_ADVANCEDLOGICCORPTINYJ:
    return "Advanced Logic Corp. TinyJ embedded processor family";
  case MT_AMDX8664:
    return "AMD x86-64";
  case MT_SONYDSP:
    return "Sony DSP Processor";
  case MT_DIGITALPDP10:
    return "Digital Equipment Corp. PDP-10";
  case MT_DIGITALPDP11:
    return "Digital Equipment Corp. PDP-11";
  case MT_SIENEBSFX66:
    return "Siemens FX66 microcontroller";
  case MT_STMICROELECTRONICSST9:
    return "STMicroelectronics ST9+ 8/16-bit microcontroller";
  case MT_STMICROELECTRONICSST7:
    return "STMicroelectronics ST7 8-bit microcontroller";
  case MT_MOTOROLAMC68HC16:
    return "Motorola MC68HC16 Microcontroller";
  case MT_MOTOROLAMC68HC11:
    return "Motorola MC68HC11 Microcontroller";
  case MT_MOTOROLAMC68HC08:
    return "Motorola MC68HC08 Microcontroller";
  case MT_MOTOROLAMC68HC05:
    return "Motorola MC68HC05 Microcontroller";
  case MT_SILICONGRAPHICSSVX:
    return "Silicon Graphics SVx";
  case MT_STMICROELECTRONICSST198:
    return "STMicroelectronics ST19 8-bit microcontroller";
  case MT_DIGITALVAX:
    return "Digital VAX";
  case MT_AXIS32_EMBEDDED:
    return "Axis Communications 32-bit embedded processor";
  case MT_INFININEON32_EMBEDDED:
    return "Infineon Technologies 32-bit embedded processor";
  case MT_ELEMENT64DSP:
    return "Element 14 64-bit DSP Processor";
  case MT_LSI16DSP:
    return "LSI Logic 16-bit DSP Processor";
  case MT_TMS320C6000:
    return "TMS320C6000";
  case MT_MCSTELBRUS:
    return "MCST Elbrus e2k";
  case MT_ARM64:
    return "Arm 64-bits";
  case MT_ZILOGZ80:
    return "Zilog Z80";
  case MT_RISCV:
    return "RISC-V";
  case MT_BPF:
    return "Berkeley Packet Filter";
  case MT_WDC:
    return "WDC 65C816";
  case MT_LOONGARCH:
    return "LoongArch";
  default:
    return "Unknown";
  }
}
