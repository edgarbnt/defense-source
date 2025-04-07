/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** file
*/

#include "../include/utils.h"
#include "../include/elf_parser.h"

bool is_option(const char *arg)
{
    return arg[0] == '-';
}

bool has_option(const char *arg, char option)
{
    if (!is_option(arg)) {
        return false;
    }
    for (size_t i = 1; arg[i] != '\0'; i++) {
        if (arg[i] == option) {
            return true;
        }
    }
    return false;
}

Elf32_Ehdr *get_elf32_header(elf_file_t *elf_file)
{
    if (!is_elf_file(elf_file) || is_64bit_elf(elf_file))
        return NULL;
    return (Elf32_Ehdr *)elf_file->data;
}

Elf64_Ehdr *get_elf64_header(elf_file_t *elf_file)
{
    if (!is_elf_file(elf_file) || !is_64bit_elf(elf_file))
        return NULL;
    return (Elf64_Ehdr *)elf_file->data;
}

void print_usage(void)
{
    printf("Usage: my_objdump [option(s)] [file(s)]\n");
    printf(" Display information from object <file(s)>.\n");
    printf(" At least one of the following switches must be given:\n");
    printf("  -f            Display the file header\n");
    printf("  -s            Display the full contents of all sections\n");
}
