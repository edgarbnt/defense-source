/*
** EPITECH PROJECT, 2025
** nm
** File description:
** file
*/

#ifndef SYMBOL_TABLE_H
    #define SYMBOL_TABLE_H

    #include <elf.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include "elf_parser.h"

typedef struct {
    char *name;
    Elf64_Addr value;
    unsigned char type;
    unsigned char bind;
    unsigned char visibility;
    Elf64_Section section_index;
} symbol_t;

typedef struct {
    elfFile_t *elf_file;
    Elf64_Shdr *sym_section;
    size_t sym_count;
    Elf64_Sym *sym_table;
    const char *filename;
} symbolContext_t;


int initialize_symbols(symbolContext_t *ctx);
symbol_t *allocate_symbols(size_t sym_count);
size_t populate_symbols(Elf64_Sym *sym_table,
    size_t sym_count, char *str_table, symbol_t *symbols);
int process_symbols(elfFile_t *elf_file, const char *filename);
char get_symbol_type(symbol_t *symbol, Elf64_Shdr *section_headers, size_t);
void display_symbols(const symbol_t *symbols, size_t i, char type);
int compare_symbols(const void *a, const void *b);

#endif /* SYMBOL_TABLE_H */
