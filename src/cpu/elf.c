#include "../include/cpu/elf.h"

bool elf_check_file(uint8_t *data)
{
    elf_header_t *header = (elf_header_t *) data;
    if (!data || !header) 
        return false;

    bool magic = header->e_ident[EI_MAG0] == ELFMAG0 && header->e_ident[EI_MAG1] == ELFMAG1 &&
        header->e_ident[EI_MAG2] == ELFMAG2 && header->e_ident[EI_MAG3] == ELFMAG3;

    bool supported = header->e_ident[EI_CLASS] == ELFCLASS32 && header->e_ident[EI_DATA] == ELFDATA2LSB &&
        header->e_machine == EM_386 && header->e_ident[EI_VERSION] == EV_CURRENT &&
        header->e_type == ET_EXEC;

    return magic && supported;
}

void elf_start(uint8_t *data)
{
	elf_header_t *header = (elf_header_t *) data;

	elf_prog_header_t *ph = (elf_prog_header_t *) (data + header->e_phoff);
	for (uint32_t i = 0; i < header->e_phnum; i++, ph++)
    {
		if (ph->p_type != 1)
            continue;

		memcpy((void *) ph->p_vaddr, data + ph->p_offset, ph->p_filesz);
	}

	entry_point_t entry_point = (entry_point_t) header->e_entry;
	entry_point();
}
