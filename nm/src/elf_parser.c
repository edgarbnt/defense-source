/*
** EPITECH PROJECT, 2025
** nm
** File description:
** file
*/

#include "../include/elf_parser.h"
#include "../include/error_handler.h"

static void display_trucked_error(const char *filename)
{
    fprintf(stderr, "bfd plugin: %s: file too short\n", filename);
    fprintf(stderr, "nm: warning: %s has a section extending"
                    " past end of file\n", filename);
    fprintf(stderr, "nm: %s: file format not recognized\n", filename);
}

static int check_truncated_file(elfFile_t *elf_file, const char *filename)
{
    Elf64_Ehdr *header = get_elf_header(elf_file);
    Elf64_Shdr *sections = get_section_headers(elf_file);
    size_t section_end;

    if (elf_file->size < sizeof(Elf64_Ehdr)) {
        display_trucked_error(filename);
        return 0;
    }
    if (header->e_shoff >= elf_file->size) {
        display_trucked_error(filename);
        return 0;
    }
    for (int i = 0; i < header->e_shnum; i++) {
        section_end = (size_t)sections[i].sh_offset + sections[i].sh_size;
        if (section_end > elf_file->size) {
            display_trucked_error(filename);
            return 0;
        }
    }
    return 1;
}

static int handle_error(const char *filename,
    elfFile_t *elf_file, struct stat *st)
{
    if (elf_file->fd == -1) {
        file_error(filename, strerror(errno));
        return 0;
    }
    if (fstat(elf_file->fd, st) == -1) {
        close(elf_file->fd);
        file_error(filename, strerror(errno));
        return 0;
    }
    elf_file->size = (*st).st_size;
    return 1;
}

int open_elf_file(const char *filename, elfFile_t *elf_file)
{
    struct stat st;

    elf_file->fd = open(filename, O_RDONLY);
    if (handle_error(filename, elf_file, &st) == 0)
        return 0;
    elf_file->data = mmap(NULL, elf_file->size,
        PROT_READ, MAP_PRIVATE, elf_file->fd, 0);
    if (elf_file->data == MAP_FAILED) {
        close(elf_file->fd);
        file_error(filename, strerror(errno));
        return 0;
    }
    if (!check_truncated_file(elf_file, filename)) {
        close_elf_file(elf_file);
        return 0;
    }
    return 1;
}

void close_elf_file(elfFile_t *elf_file)
{
    if (elf_file->data != NULL && elf_file->data != MAP_FAILED)
        munmap(elf_file->data, elf_file->size);
    if (elf_file->fd != -1)
        close(elf_file->fd);
}

Elf64_Ehdr *get_elf_header(elfFile_t *elf_file)
{
    return (Elf64_Ehdr *)elf_file->data;
}

Elf64_Shdr *get_section_headers(elfFile_t *elf_file)
{
    Elf64_Ehdr *header = get_elf_header(elf_file);

    return (Elf64_Shdr *)((char *)elf_file->data + header->e_shoff);
}

static char *get_string_table(elfFile_t *elf_file)
{
    Elf64_Ehdr *header = get_elf_header(elf_file);
    Elf64_Shdr *section_headers = get_section_headers(elf_file);

    if (header->e_shstrndx == SHN_UNDEF ||
        header->e_shstrndx >= header->e_shnum)
        return NULL;
    return (char *)elf_file->data +
        section_headers[header->e_shstrndx].sh_offset;
}

Elf64_Sym *get_symbol_table(elfFile_t *elf_file,
    Elf64_Shdr **sym_section, size_t *sym_count)
{
    Elf64_Ehdr *header = get_elf_header(elf_file);
    Elf64_Shdr *heads = get_section_headers(elf_file);
    char *strtab = get_string_table(elf_file);

    if (!strtab)
        return NULL;
    for (int i = 0; i < header->e_shnum; i++)
        if (heads[i].sh_type == SHT_SYMTAB) {
            *sym_section = &heads[i];
            *sym_count = heads[i].sh_size / heads[i].sh_entsize;
            return (Elf64_Sym *)((char *)elf_file->data + heads[i].sh_offset);
        }
    for (int i = 0; i < header->e_shnum; i++)
        if (heads[i].sh_type == SHT_DYNSYM) {
            *sym_section = &heads[i];
            *sym_count = heads[i].sh_size / heads[i].sh_entsize;
            return (Elf64_Sym *)((char *)elf_file->data + heads[i].sh_offset);
        }
    return NULL;
}
