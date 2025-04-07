/*
** EPITECH PROJECT, 2025
** nm
** File description:
** file
*/

#include <stdio.h>
#include <string.h>
#include "../include/elf_parser.h"
#include "../include/error_handler.h"
#include "../include/symbol_table.h"
#include "../include/utils.h"

static int is_valid_elf(elfFile_t *elf_file)
{
    Elf64_Ehdr *header = (Elf64_Ehdr *)elf_file->data;

    if (memcmp(header->e_ident, ELFMAG, SELFMAG) != 0)
        return 0;
    if (header->e_ident[EI_CLASS] != ELFCLASS32 &&
        header->e_ident[EI_CLASS] != ELFCLASS64)
        return 0;
    if (header->e_ident[EI_DATA] != ELFDATA2LSB &&
        header->e_ident[EI_DATA] != ELFDATA2MSB)
        return 0;
    return 1;
}

int process_file(const char *filename, int multiple_files)
{
    elfFile_t elf_file = {NULL, 0, -1};
    int result = 0;

    if (multiple_files)
        printf("\n%s:\n", filename);
    if (!open_elf_file(filename, &elf_file))
        return 0;
    if (!is_valid_elf(&elf_file)) {
        close_elf_file(&elf_file);
        format_error(filename);
        return 0;
    }
    result = process_symbols(&elf_file, filename);
    close_elf_file(&elf_file);
    return result;
}

static void process_files(int argc, char *argv[], int *status)
{
    int multiple_files = (argc > 2);

    for (int i = 1; i < argc; i++) {
        if (!file_exists(argv[i])) {
            *status = 84;
            continue;
        }
        if (!process_file(argv[i], multiple_files)) {
            *status = 84;
        }
    }
}

int main(int argc, char *argv[])
{
    int status = 0;

    if (argc < 2) {
        if (file_exists("a.out")) {
            status = process_file("a.out", 0) ? 0 : 84;
        } else {
            fprintf(stderr, "nm: 'a.out': No such file\n");
            status = 84;
        }
    } else
        process_files(argc, argv, &status);
    return status;
}
