/*
** EPITECH PROJECT, 2023
** nm
** File description:
** nm
*/

#include "../../include/symbol_table.h"
#include "../../include/utils.h"

static char get_symbol_type_by_section(Elf64_Shdr *section, char default_type)
{
    if (section->sh_type == SHT_NOBITS && (section->sh_flags & SHF_ALLOC))
        return 'B';
    if (section->sh_type == SHT_PROGBITS && (section->sh_flags & SHF_ALLOC) &&
        (section->sh_flags & SHF_EXECINSTR))
        return 'T';
    if ((section->sh_type == SHT_PROGBITS && (section->sh_flags & SHF_ALLOC) &&
        (section->sh_flags & SHF_WRITE)) || section->sh_type == SHT_DYNAMIC)
        return 'D';
    if ((section->sh_type == SHT_PROGBITS ||
        section->sh_type == SHT_INIT_ARRAY ||
        section->sh_type == SHT_FINI_ARRAY) && (section->sh_flags & SHF_ALLOC))
        return 'R';
    if (section->sh_type == SHT_INIT_ARRAY ||
        section->sh_type == SHT_FINI_ARRAY)
        return 'd';
    if (section->sh_type == SHT_PROGBITS || section->sh_type == SHT_NOTE)
        return 'N';
    return default_type;
}

static char get_specific_symbol_type(symbol_t *symbol, size_t shnum, char c)
{
    if (strcmp(symbol->name, "__gmon_start__") == 0)
        return 'w';
    if (symbol->section_index == SHN_UNDEF)
        return 'U';
    if (symbol->section_index == SHN_ABS)
        return 'A';
    if (symbol->section_index == SHN_COMMON)
        return 'C';
    if (symbol->section_index >= shnum)
        return '?';
    return c;
}

char get_t_and_r_symbols(const Elf64_Shdr *section, symbol_t *symbol)
{
    if (section->sh_flags & SHF_EXECINSTR)
        return (symbol->bind == STB_LOCAL) ? 't' : 'T';
    if ((section->sh_flags & SHF_ALLOC) && !(section->sh_flags & SHF_WRITE))
        return (symbol->bind == STB_LOCAL) ? 'r' : 'R';
    return 0;
}

char get_symbol_type(symbol_t *symbol, Elf64_Shdr *headers, size_t shnum)
{
    char c = get_symbol_type_by_section(&headers[symbol->section_index], '?');
    Elf64_Shdr *section = NULL;

    if (symbol->section_index != SHN_UNDEF) {
        section = &headers[symbol->section_index];
        if (strcmp(symbol->name, "__abi_tag") == 0)
            return (symbol->bind == STB_LOCAL) ? 'r' : 'R';
        if (section->sh_type == SHT_PROGBITS &&
            get_t_and_r_symbols(section, symbol) != 0) {
            return get_t_and_r_symbols(section, symbol);
        }
        if (section->sh_type == SHT_INIT_ARRAY ||
            section->sh_type == SHT_FINI_ARRAY)
            return 'd';
    }
    if (symbol->bind == STB_WEAK)
        return (symbol->section_index == SHN_UNDEF) ? 'w' : 'W';
    if (symbol->bind == STB_LOCAL && c != '?')
        return tolower(c);
    return get_specific_symbol_type(symbol, shnum, c);
}
