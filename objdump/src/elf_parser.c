/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** file
*/

#include "../include/elf_parser.h"
#include "../include/error_handler.h"
#include <errno.h>
#include <sys/mman.h>

static bool map_elf_file(const char *filename, elf_file_t *elf_file)
{
    elf_file->data = mmap(NULL, elf_file->size, PROT_READ, MAP_PRIVATE,
        elf_file->fd, 0);
    if (elf_file->data == MAP_FAILED) {
        print_file_error(filename, strerror(errno));
        close(elf_file->fd);
        return false;
    }
    return true;
}

static bool check_file_stat(const char *filename, elf_file_t *elf_file)
{
    struct stat st;

    if (fstat(elf_file->fd, &st) == -1) {
        print_file_error(filename, strerror(errno));
        close(elf_file->fd);
        return false;
    }
    elf_file->size = st.st_size;
    return true;
}

bool open_elf_file(const char *filename, elf_file_t *elf_file)
{
    elf_file->fd = open(filename, O_RDONLY);
    if (elf_file->fd == -1) {
        fprintf(stderr, "objdump: '%s': %s\n", filename, "No such file");
        return false;
    }
    if (!check_file_stat(filename, elf_file))
        return false;
    if (!map_elf_file(filename, elf_file))
        return false;
    elf_file->filename = strdup(filename);
    elf_file->is_64 = is_64bit_elf(elf_file);
    elf_file->is_big_endian = is_big_endian_elf(elf_file);
    if (!check_truncated_file(elf_file)) {
        close_elf_file(elf_file);
        return false;
    }
    return true;
}

void close_elf_file(elf_file_t *elf_file)
{
    if (elf_file->data && elf_file->data != MAP_FAILED)
        munmap(elf_file->data, elf_file->size);
    if (elf_file->fd != -1)
        close(elf_file->fd);
    if (elf_file->filename)
        free(elf_file->filename);
    elf_file->data = NULL;
    elf_file->fd = -1;
    elf_file->filename = NULL;
}

bool is_64bit_elf(elf_file_t *elf_file)
{
    unsigned char *e_ident;

    if (!is_elf_file(elf_file))
        return false;
    e_ident = (unsigned char *)elf_file->data;
    return e_ident[EI_CLASS] == ELFCLASS64;
}

bool is_big_endian_elf(elf_file_t *elf_file)
{
    unsigned char *e_ident;

    if (!is_elf_file(elf_file))
        return false;
    e_ident = (unsigned char *)elf_file->data;
    return e_ident[EI_DATA] == ELFDATA2MSB;
}

static void set_32bit_format(char *format, elf_file_t *elf_file)
{
    Elf32_Ehdr *header;

    if (is_big_endian_elf(elf_file)) {
        strcpy(format, "elf32-big");
        return;
    }
    header = get_elf32_header(elf_file);
    if (header && header->e_machine == EM_386)
        strcpy(format, "elf32-i386");
    else
        strcpy(format, "elf32-little");
}

static void set_64bit_format(char *format, elf_file_t *elf_file)
{
    Elf64_Ehdr *header;

    if (is_big_endian_elf(elf_file)) {
        strcpy(format, "elf64-big");
        return;
    }
    header = get_elf64_header(elf_file);
    if (header && header->e_machine == EM_X86_64)
        strcpy(format, "elf64-x86-64");
    else
        strcpy(format, "elf64-little");
}

const char *get_elf_format(elf_file_t *elf_file)
{
    static char format[32];

    if (is_64bit_elf(elf_file))
        set_64bit_format(format, elf_file);
    else
        set_32bit_format(format, elf_file);
    return format;
}
