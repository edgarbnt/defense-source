/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** file
*/

#ifndef FILE_HEADER_H
    #define FILE_HEADER_H

    #include "elf_parser.h"
    #include <errno.h>
    #include <sys/mman.h>
    #include <unistd.h>
    #include <fcntl.h>


void display_truncated_error(const char *filename);
bool check_truncated_file(elf_file_t *elf_file);
void print_file_error(const char *filename, const char *message);
void display_file_header(elf_file_t *elf_file);
void display_file_header_32(elf_file_t *elf_file, Elf32_Ehdr *header);
void display_file_header_64(elf_file_t *elf_file, Elf64_Ehdr *header);
const char *get_file_type(uint16_t e_type);
const char *get_machine_name(uint16_t e_machine);
const char *get_file_flags_meaning(uint16_t e_flags, uint16_t e_machine);

#endif /* FILE_HEADER_H */
