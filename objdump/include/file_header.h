/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** file
*/

#ifndef FILE_HEADER_H
    #define FILE_HEADER_H

    #include "elf_parser.h"

void display_file_header(elf_file_t *elf_file);
void display_file_header_32(Elf32_Ehdr *header);
void display_file_header_64(Elf64_Ehdr *header);
const char *get_file_type(uint16_t e_type);
const char *get_machine_name(uint16_t e_machine);
const char *get_file_flags_meaning(uint16_t e_type);
uint16_t get_file_flags(Elf64_Ehdr *header);

#endif /* FILE_HEADER_H */
