/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** file
*/

#include "../include/elf_parser.h"
#include "../include/error_handler.h"
#include "../include/file_header.h"
#include "../include/utils.h"
#include "../include/section_display.h"

static int handle_elf_error(elf_file_t *elf_file, const char *filename)
{
    print_file_error(filename, "file format not recognized");
    close_elf_file(elf_file);
    return 84;
}

static void display_elf_info(const char *filename, elf_file_t *elf_file)
{
    printf("\n%s:     file format %s\n", filename, get_elf_format(elf_file));
    display_file_header(elf_file);
}

static int process_file(const char *filename, bool f_flag, bool s_flag)
{
    elf_file_t elf_file;

    if (!open_elf_file(filename, &elf_file))
        return 84;
    if (!is_elf_file(&elf_file))
        return handle_elf_error(&elf_file, filename);
    if (f_flag)
        display_elf_info(filename, &elf_file);
    if (s_flag) {
        if (!f_flag)
            printf("\n%s:     file format %s\n\n", filename,
                get_elf_format(&elf_file));
        display_all_sections(&elf_file);
    }
    close_elf_file(&elf_file);
    return 0;
}

static void parse_flags(int argc, char *argv[], bool *f_flag, bool *s_flag)
{
    for (int i = 1; i < argc; i++) {
        if (!is_option(argv[i]))
            continue;
        if (has_option(argv[i], 'f'))
            *f_flag = true;
        if (has_option(argv[i], 's'))
            *s_flag = true;
        if (has_option(argv[i], 'h')) {
            print_usage();
            exit(0);
        }
    }
}

static int process_files(int argc, char *argv[], bool f_flag, bool s_flag)
{
    int ret = 0;
    int processed = 0;

    for (int i = 1; i < argc; i++) {
        if (!is_option(argv[i])) {
            ret = process_file(argv[i], f_flag, s_flag);
            processed++;
        }
    }
    if (processed == 0)
        ret = process_file("a.out", f_flag, s_flag);
    return ret;
}

int main(int argc, char *argv[])
{
    bool f_flag = false;
    bool s_flag = false;

    parse_flags(argc, argv, &f_flag, &s_flag);
    if (!f_flag && !s_flag) {
        f_flag = true;
        s_flag = true;
    }
    return process_files(argc, argv, f_flag, s_flag);
}
