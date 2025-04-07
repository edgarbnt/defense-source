/*
** EPITECH PROJECT, 2023
** objdump
** File description:
** file
*/

#include "../include/file_header.h"

const char *get_file_type(uint16_t e_type)
{
    if (e_type == ET_NONE)
        return "NONE (No file type)";
    if (e_type == ET_REL)
        return "REL (Relocatable file)";
    if (e_type == ET_EXEC)
        return "EXEC (Executable file)";
    if (e_type == ET_DYN)
        return "DYN (Shared object file)";
    if (e_type == ET_CORE)
        return "CORE (Core file)";
    if (e_type == ET_LOOS || e_type == ET_HIOS)
        return "OS Specific";
    if (e_type == ET_LOPROC || e_type == ET_HIPROC)
        return "Processor Specific";
    return "Unknown";
}

static const char *get_modern_machines(uint16_t e_machine)
{
    switch (e_machine) {
    case EM_X86_64:
        return "i386:x86-64";
    case EM_AARCH64:
        return "AArch64";
    case EM_RISCV:
        return "RISC-V";
    case EM_IA_64:
        return "Intel IA-64";
    default:
        return NULL;
    }
}

static const char *get_common_machines(uint16_t e_machine)
{
    switch (e_machine) {
    case EM_386:
        return "i386";
    case EM_ARM:
        return "ARM";
    case EM_PPC:
        return "PowerPC";
    case EM_PPC64:
        return "PowerPC64";
    case EM_S390:
        return "IBM S/390";
    default:
        return NULL;
    }
}

static const char *get_legacy_machines(uint16_t e_machine)
{
    switch (e_machine) {
    case EM_NONE:
        return "None";
    case EM_M32:
        return "AT&T WE 32100";
    case EM_SPARC:
        return "SPARC";
    case EM_68K:
        return "Motorola 68000";
    case EM_88K:
        return "Motorola 88000";
    default:
        return NULL;
    }
}

static const char *get_specialized_machines(uint16_t e_machine)
{
    switch (e_machine) {
    case EM_860:
        return "Intel 80860";
    case EM_MIPS:
        return "MIPS R3000";
    case EM_PARISC:
        return "HP/PA";
    case EM_SPARC32PLUS:
        return "SPARC v8+";
    case EM_SH:
        return "Hitachi SH";
    case EM_SPARCV9:
        return "SPARC v9";
    default:
        return NULL;
    }
}

const char *get_machine_name(uint16_t e_machine)
{
    const char *name;

    name = get_modern_machines(e_machine);
    if (name != NULL)
        return name;
    name = get_common_machines(e_machine);
    if (name != NULL)
        return name;
    name = get_legacy_machines(e_machine);
    if (name != NULL)
        return name;
    name = get_specialized_machines(e_machine);
    if (name != NULL)
        return name;
    return "Unknown";
}
