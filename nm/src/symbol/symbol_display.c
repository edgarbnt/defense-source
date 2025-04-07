/*
** EPITECH PROJECT, 2023
** nm
** File description:
** nm
*/

#include "../../include/symbol_table.h"
#include "../../include/utils.h"

void display_symbols(const symbol_t *symbols, size_t i, char type)
{
    if (type == 'U' || type == 'w') {
        printf("                 %c %s\n", type, symbols[i].name);
    } else {
        printf("%016lx %c %s\n", symbols[i].value, type, symbols[i].name);
    }
}
