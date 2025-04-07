/*
** EPITECH PROJECT, 2023
** nm
** File description:
** nm
*/

#include "../../include/symbol_table.h"
#include "../../include/utils.h"
#include <ctype.h>

const char *skip_special_characters(const char *str)
{
    size_t len = strlen(str);
    size_t new_len = 0;
    char *new_str;
    size_t j = 0;

    for (size_t i = 0; i < len; i++)
        if (isalnum(str[i]))
            new_len++;
    new_str = (char *)malloc((new_len + 1) * sizeof(char));
    if (new_str == NULL)
        return NULL;
    for (size_t i = 0; i < len; i++)
        if (isalnum(str[i])) {
            new_str[j] = str[i];
            j++;
        }
    new_str[new_len] = '\0';
    return new_str;
}

int compare_symbols(const void *a, const void *b)
{
    const symbol_t *sym_a = (const symbol_t *)a;
    const symbol_t *sym_b = (const symbol_t *)b;
    const char *name_a = skip_special_characters(sym_a->name);
    const char *name_b = skip_special_characters(sym_b->name);
    int result = strcasecmp(name_a, name_b);

    if (result == 0)
        return strcasecmp(sym_a->name, sym_b->name);
    return result;
}
