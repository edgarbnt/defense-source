/*
** EPITECH PROJECT, 2023
** my_strcmp
** File description:
** function that Reproduce the behavior of the strcmp function.
*/

static int lenstr(char const *str)
{
    int compteur = 0;

    while (str[compteur] != '\0'){
        compteur ++;
    }
    return compteur;
}

static int biggersmaller(char const *s1, char const *s2, int compteur)
{
    if (s1[compteur] > s2[compteur]) {
        return 1;
    } else {
        return -1;
    }
}

static int dif1(char const *s1, char const *s2)
{
    int value = 0;
    int compteur = 0;

    for (; compteur < lenstr(s2); compteur ++) {
        if (s1[compteur] != s2[compteur]) {
            value = biggersmaller(s1, s2, compteur);
            return value;
        }
    }
    return value;
}

int my_strcmp(char const *s1, char const *s2)
{
    int len1 = lenstr(s1);
    int len2 = lenstr(s2);
    int value;

    value = dif1(s1, s2);
    if (value == 0) {
        if (len1 > len2) {
            return 1;
        }
        if (len1 < len2) {
            return -1;
        }
    }
    return value;
}
