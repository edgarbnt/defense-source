/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** file
*/

#include "../include/error_handler.h"

void display_truncated_error(const char *filename)
{
    fprintf(stderr, "objdump: warning: %s has a section extending "
                    "past end of file\n",
        filename);
    fprintf(stderr, "objdump: %s: file format not recognized\n", filename);
}

static bool check_section_size(size_t section_end, elf_file_t *elf_file)
{
    if (section_end > elf_file->size) {
        display_truncated_error(elf_file->filename);
        return false;
    }
    return true;
}

static bool check_64bit_sections(elf_file_t *elf_file)
{
    Elf64_Ehdr *header = get_elf64_header(elf_file);
    size_t section_end;

    if (header->e_shoff >= elf_file->size) {
        display_truncated_error(elf_file->filename);
        return false;
    }
    section_end = (size_t)header->e_shoff +
        (header->e_shnum * sizeof(Elf64_Shdr));
    return check_section_size(section_end, elf_file);
}

static bool check_32bit_sections(elf_file_t *elf_file)
{
    Elf32_Ehdr *header = get_elf32_header(elf_file);
    size_t section_end;

    if (header->e_shoff >= elf_file->size) {
        display_truncated_error(elf_file->filename);
        return false;
    }
    section_end = (size_t)header->e_shoff +
        (header->e_shnum * sizeof(Elf32_Shdr));
    return check_section_size(section_end, elf_file);
}

bool check_truncated_file(elf_file_t *elf_file)
{
    if (elf_file->size < sizeof(Elf32_Ehdr)) {
        display_truncated_error(elf_file->filename);
        return false;
    }
    return elf_file->is_64 ? check_64bit_sections(elf_file) :
        check_32bit_sections(elf_file);
}

bool is_elf_file(elf_file_t *elf_file)
{
    unsigned char *e_ident;

    if (elf_file->size < EI_NIDENT)
        return false;
    e_ident = (unsigned char *)elf_file->data;
    return (e_ident[EI_MAG0] == ELFMAG0 &&
        e_ident[EI_MAG1] == ELFMAG1 &&
        e_ident[EI_MAG2] == ELFMAG2 &&
        e_ident[EI_MAG3] == ELFMAG3);
}

void print_file_error(const char *filename, const char *message)
{
    fprintf(stderr, "objdump: %s: %s\n", filename, message);
}
