/*
** EPITECH PROJECT, 2025
** nm
** File description:
** file
*/

#ifndef ELF_PARSER_H
    #define ELF_PARSER_H

    #include <elf.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/mman.h>
    #include <sys/stat.h>

typedef struct {
    void *data;
    size_t size;
    int fd;
} elfFile_t;

int open_elf_file(const char *filename, elfFile_t *elf_file);
void close_elf_file(elfFile_t *elf_file);
Elf64_Ehdr *get_elf_header(elfFile_t *elf_file);
Elf64_Shdr *get_section_headers(elfFile_t *elf_file);
Elf64_Sym *get_symbol_table(elfFile_t *elf_file,
    Elf64_Shdr **sym_section, size_t *sym_count);

#endif /* ELF_PARSER_H */
