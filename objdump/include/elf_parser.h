/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** file
*/

#ifndef ELF_PARSER_H
    #define ELF_PARSER_H

    #include <elf.h>
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <fcntl.h>

typedef struct {
    void *data;
    size_t size;
    int fd;
    char *filename;
    bool is_64;
    bool is_big_endian;
} elf_file_t;

bool open_elf_file(const char *filename, elf_file_t *elf_file);
void close_elf_file(elf_file_t *elf_file);
bool is_elf_file(elf_file_t *elf_file);
bool is_64bit_elf(elf_file_t *elf_file);
bool is_big_endian_elf(elf_file_t *elf_file);
const char *get_elf_format(elf_file_t *elf_file);

Elf32_Ehdr *get_elf32_header(elf_file_t *elf_file);
Elf64_Ehdr *get_elf64_header(elf_file_t *elf_file);

#endif /* ELF_PARSER_H */
