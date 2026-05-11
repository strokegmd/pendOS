#ifndef __ELF_H
#define __ELF_H

#include <stdint.h>
#include <stdbool.h>

#include "../lib/string.h"
#include "../drivers/tty.h"

#define ELF_NIDENT 16

#define ELFMAG0	0x7F
#define ELFMAG1	'E'
#define ELFMAG2	'L'
#define ELFMAG3	'F'

#define ELFDATA2LSB	(1)
#define ELFCLASS32	(1)

#define EM_386		(3)
#define EV_CURRENT	(1)

typedef struct
{
    uint8_t  e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry;
    uint32_t e_phoff;
    uint32_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} elf_header_t;

typedef struct
{
    uint32_t p_type;
    uint32_t p_offset;
    uint32_t p_vaddr;
    uint32_t p_paddr;
    uint32_t p_filesz;
    uint32_t p_memsz;
    uint32_t p_flags;
    uint32_t p_align;
} elf_prog_header_t;

typedef enum 
{
	EI_MAG0		  = 0,
	EI_MAG1		  = 1,
	EI_MAG2		  = 2,
	EI_MAG3		  = 3,
	EI_CLASS	  = 4,
	EI_DATA		  = 5,
	EI_VERSION	  = 6,
	EI_OSABI	  = 7,
	EI_ABIVERSION = 8,
	EI_PAD		  = 9,
} elf_ident_t;

typedef enum 
{
	ET_NONE		= 0,
	ET_REL		= 1,
	ET_EXEC		= 2,
} elf_type_t;

typedef void (*entry_point_t)(void);

bool elf_check_file(uint8_t *data);
void elf_start(uint8_t *data);

#endif
