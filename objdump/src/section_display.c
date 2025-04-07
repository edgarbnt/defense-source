/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** file
*/

#include "../include/section_display.h"

static void handle_64bit_section(Elf64_Shdr *section, elf_file_t *elf_file,
    const char *name)
{
    if (should_display_section(name, section->sh_type))
        display_section_contents_64(elf_file, section, name);
}

static void process_64bit_sections(elf_file_t *elf_file)
{
    Elf64_Ehdr *header;
    Elf64_Shdr *sections;
    Elf64_Shdr *shstrtab;
    const char *shstrtab_data;
    uint16_t i;

    header = get_elf64_header(elf_file);
    if (!header)
        return;
    sections = (Elf64_Shdr *)((char *)elf_file->data + header->e_shoff);
    shstrtab = &sections[header->e_shstrndx];
    shstrtab_data = (const char *)elf_file->data + shstrtab->sh_offset;
    for (i = 0; i < header->e_shnum; i++) {
        handle_64bit_section(&sections[i], elf_file,
            shstrtab_data + sections[i].sh_name);
    }
}

static void handle_32bit_section(Elf32_Shdr *section, elf_file_t *elf_file,
    const char *name)
{
    if (should_display_section(name, section->sh_type))
        display_section_contents_32(elf_file, section, name);
}

static void process_32bit_sections(elf_file_t *elf_file)
{
    Elf32_Ehdr *header;
    Elf32_Shdr *sections;
    Elf32_Shdr *shstrtab;
    const char *shstrtab_data;
    uint16_t i;

    header = get_elf32_header(elf_file);
    if (!header)
        return;
    sections = (Elf32_Shdr *)((char *)elf_file->data + header->e_shoff);
    shstrtab = &sections[header->e_shstrndx];
    shstrtab_data = (const char *)elf_file->data + shstrtab->sh_offset;
    for (i = 0; i < header->e_shnum; i++) {
        handle_32bit_section(&sections[i], elf_file,
            shstrtab_data + sections[i].sh_name);
    }
}

void display_all_sections(elf_file_t *elf_file)
{
    if (is_64bit_elf(elf_file))
        process_64bit_sections(elf_file);
    else
        process_32bit_sections(elf_file);
}

static void print_hex_line(const unsigned char *data, size_t offset,
    size_t size, uint64_t addr)
{
    char ascii[17];

    printf(" %04lx", addr + offset);
    for (size_t j = 0; j < 16; j++) {
        if (j % 4 == 0)
            printf(" ");
        if (offset + j < size) {
            printf("%02x", data[offset + j]);
            ascii[j] = get_printable_char(data[offset + j]);
        } else {
            printf("  ");
            ascii[j] = ' ';
        }
    }
    ascii[16] = '\0';
    printf("  %s\n", ascii);
}

void display_section_contents_32(elf_file_t *elf_file, Elf32_Shdr *section,
    const char *name)
{
    const unsigned char *data;

    if (section->sh_size == 0 || section->sh_type == SHT_NOBITS)
        return;
    printf("Contents of section %s:\n", name);
    data = (const unsigned char *)elf_file->data + section->sh_offset;
    for (size_t i = 0; i < section->sh_size; i += 16)
        print_hex_line(data, i, section->sh_size, section->sh_addr);
}

void display_section_contents_64(elf_file_t *elf_file, Elf64_Shdr *section,
    const char *name)
{
    const unsigned char *data;

    if (section->sh_size == 0 || section->sh_type == SHT_NOBITS)
        return;
    printf("Contents of section %s:\n", name);
    data = (const unsigned char *)elf_file->data + section->sh_offset;
    for (size_t i = 0; i < section->sh_size; i += 16)
        print_hex_line(data, i, section->sh_size, section->sh_addr);
}

bool should_display_section(const char *name, uint32_t type)
{
    if (!name || name[0] == '\0')
        return false;
    if (type == SHT_NOBITS || type == SHT_NULL)
        return false;
    if (strcmp(name, ".strtab") == 0 || strcmp(name, ".symtab") == 0 ||
        strcmp(name, ".shstrtab") == 0)
        return false;
    return true;
}

char get_printable_char(unsigned char c)
{
    return (c >= 32 && c <= 126) ? (char)c : '.';
}
