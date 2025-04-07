/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** file
*/

#ifndef SECTION_DISPLAY_H
    #define SECTION_DISPLAY_H

    #include "elf_parser.h"

void display_all_sections(elf_file_t *elf_file);
void display_section_contents_32(elf_file_t *elf_file, Elf32_Shdr *section,
    const char *name);
void display_section_contents_64(elf_file_t *elf_file, Elf64_Shdr *section,
    const char *name);
bool should_display_section(const char *name, uint32_t type);
void print_hex_dump(const unsigned char *data, size_t size, uint64_t addr);
char get_printable_char(unsigned char c);

#endif /* SECTION_DISPLAY_H */
