/*
** EPITECH PROJECT, 2025
** nm
** File description:
** file
*/

#include "../../include/symbol_table.h"
#include "../../include/utils.h"

static char *get_string_tables(elfFile_t *elf_file,
    Elf64_Shdr *section_headers, Elf64_Shdr *sym_section)
{
    char *str_table;

    str_table = (char *)elf_file->data +
        section_headers[sym_section->sh_link].sh_offset;
    return str_table;
}

symbol_t *initialize_and_allocate_symbols(symbolContext_t *ctx,
    Elf64_Shdr *headers, size_t *valid_count)
{
    symbol_t *symb;
    char *table;

    if (!initialize_symbols(ctx)) {
        return NULL;
    }
    symb = allocate_symbols(ctx->sym_count);
    if (!symb) {
        return NULL;
    }
    table = get_string_tables(ctx->elf_file, headers, ctx->sym_section);
    *valid_count = populate_symbols(
        ctx->sym_table, ctx->sym_count, table, symb);
    qsort(symb, *valid_count, sizeof(symbol_t), compare_symbols);
    return symb;
}

int process_symbols(elfFile_t *elf_file, const char *filename)
{
    Elf64_Ehdr *header = get_elf_header(elf_file);
    Elf64_Shdr *headers = get_section_headers(elf_file);
    symbolContext_t ctx;
    size_t valid_count;
    symbol_t *symb;

    ctx.elf_file = elf_file;
    ctx.filename = filename;
    ctx.sym_section = NULL;
    ctx.sym_count = 0;
    symb = initialize_and_allocate_symbols(&ctx, headers, &valid_count);
    if (!symb)
        return 0;
    for (size_t i = 0; i < valid_count; i++)
        display_symbols(symb, i,
            get_symbol_type(&symb[i], headers, header->e_shnum));
    free(symb);
    return 1;
}
