/*
** EPITECH PROJECT, 2023
** nm
** File description:
** nm
*/

#include "../../include/symbol_table.h"
#include "../../include/error_handler.h"
#include "../../include/utils.h"

int initialize_symbols(symbolContext_t *ctx)
{
    ctx->sym_table = get_symbol_table(
        ctx->elf_file, &ctx->sym_section, &ctx->sym_count);
    if (!ctx->sym_table || ctx->sym_count == 0) {
        fprintf(stderr, "%s: no symbols\n", ctx->filename);
        return 0;
    }
    return 1;
}

symbol_t *allocate_symbols(size_t sym_count)
{
    symbol_t *symbols = malloc(sym_count * sizeof(symbol_t));

    if (!symbols)
        fatal_error("Memory allocation failed");
    return symbols;
}

size_t populate_symbols(Elf64_Sym *sym_table, size_t sym_count,
    char *str_table, symbol_t *symbols)
{
    size_t valid_count = 0;

    for (size_t i = 0; i < sym_count; i++) {
        if (sym_table[i].st_name == 0 ||
            ELF64_ST_TYPE(sym_table[i].st_info) == STT_FILE)
            continue;
        symbols[valid_count].name = &str_table[sym_table[i].st_name];
        symbols[valid_count].value = sym_table[i].st_value;
        symbols[valid_count].type = ELF64_ST_TYPE(sym_table[i].st_info);
        symbols[valid_count].bind = ELF64_ST_BIND(sym_table[i].st_info);
        symbols[valid_count].visibility = ELF64_ST_VISIBILITY(
                sym_table[i].st_other);
        symbols[valid_count].section_index = sym_table[i].st_shndx;
        valid_count++;
    }
    return valid_count;
}
