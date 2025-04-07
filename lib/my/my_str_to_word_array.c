/*
** EPITECH PROJECT, 2024
** str_to_word_array
** File description:
** main.c
*/

#include "../../include/my.h"

int is_del(char el, const char *del)
{
    for (int i = 0; del[i] != '\0'; i ++) {
        if (del[i] == el)
            return 1;
    }
    return 0;
}

int count_words(char *str, char *del)
{
    int i = 0;
    int len = my_strlen(str);
    int count = 0;

    while (is_del(str[i], del) == 1)
        i ++;
    if (str[i] == '\0')
        return 0;
    else
        count ++;
    while (str[i] != '\0') {
        if (is_del(str[i], del) == 1 && (i + 1 != len) &&
            is_del(str[i + 1], del) == 0) {
            count ++;
        }
        i ++;
    }
    return count;
}

void malloc_tab(char **cut_str, char *str, char *del)
{
    int i = 0;
    int word = 0;
    int len = my_strlen(str);
    int position = 0;

    while (is_del(str[i], del) == 1)
        i ++;
    while (str[i] != '\0') {
        if (is_del(str[i], del) == 0)
            word ++;
        if ((is_del(str[i], del) == 1 && (i + 1 != len) &&
            is_del(str[i + 1], del) == 0) || str[i + 1] == '\0') {
            cut_str[position] = malloc(sizeof(char) * (word + 1));
            cut_str[position][word] = '\0';
            position ++;
            word = 0;
        }
        i ++;
    }
}

void my_str_to_word_array2(char *str, char *del, int i, char **cut_str)
{
    int position = 0;
    int pos2 = 0;
    int len = my_strlen(str);

    while (str[i] != '\0' && cut_str[position] != NULL) {
        if (is_del(str[i], del) == 0) {
            cut_str[position][pos2] = str[i];
            pos2 ++;
        }
        if (is_del(str[i], del) == 1 && (i + 1 != len) &&
            is_del(str[i + 1], del) == 0) {
            position ++;
            pos2 = 0;
        }
        i ++;
    }
}

char **my_str_to_word_array(char *str, char *del)
{
    int words = count_words(str, del);
    char **cut_str;
    int i = 0;

    if (words == 0)
        return NULL;
    cut_str = malloc(sizeof(char *) * (words + 1));
    malloc_tab(cut_str, str, del);
    while (is_del(str[i], del) == 1)
        i ++;
    my_str_to_word_array2(str, del, i, cut_str);
    cut_str[words] = NULL;
    return cut_str;
}
