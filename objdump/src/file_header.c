/*
** EPITECH PROJECT, 2023
** objdump
** File description:
** file
*/

#include "../include/file_header.h"

static void display_header_64(Elf64_Ehdr *header)
{
    if (header) {
        display_file_header_64(header);
    }
}

static void display_header_32(Elf32_Ehdr *header)
{
    if (header) {
        display_file_header_32(header);
    }
}

void display_file_header(elf_file_t *elf_file)
{
    if (is_64bit_elf(elf_file)) {
        display_header_64(get_elf64_header(elf_file));
    } else {
        display_header_32(get_elf32_header(elf_file));
    }
}

void display_file_header_32(Elf32_Ehdr *header)
{
    printf("architecture: %s, flags 0x%08x:\n",
        get_machine_name(header->e_machine),
        header->e_flags);
    printf("%s\n", get_file_flags_meaning(header->e_type));
    printf("start address 0x%08x\n\n", header->e_entry);
}

void display_file_header_64(Elf64_Ehdr *header)
{
    printf("architecture: %s, flags 0x%08x:\n",
        get_machine_name(header->e_machine),
        get_file_flags(header));
    printf("%s\n", get_file_flags_meaning(header->e_type));
    printf("start address 0x%016lx\n\n", header->e_entry);
}

uint16_t get_file_flags(Elf64_Ehdr *header)
{
    uint16_t flags = 0;

    if (header->e_type == ET_EXEC) {
        flags |= 0x0002;
    }
    if (header->e_type == ET_DYN) {
        flags |= 0x0010;
    }
    flags |= 0x0010;
    if (header->e_type == ET_EXEC || header->e_type == ET_DYN) {
        flags |= 0x0100;
    }
    return flags;
}

const char *get_file_flags_meaning(uint16_t e_type)
{
    static char buffer[256];

    buffer[0] = '\0';
    if (e_type == ET_EXEC)
        strcat(buffer, "EXEC_P");
    if (e_type == ET_DYN) {
        if (buffer[0] != '\0')
            strcat(buffer, ", ");
        strcat(buffer, "DYNAMIC");
    }
    if (buffer[0] != '\0')
        strcat(buffer, ", ");
    strcat(buffer, "HAS_SYMS");
    if (e_type == ET_EXEC || e_type == ET_DYN) {
        strcat(buffer, ", ");
        strcat(buffer, "D_PAGED");
    }
    return buffer;
}
