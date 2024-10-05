/*
** EPITECH PROJECT, 2021
** epitech
** File description:
** my_revstr.c
*/

#include "shared.h"

int my_intlen(long long number, int div)
{
    int count = 0;
    for (; number > 0; number = number / div) {
        count++;
    }
    return count;
}

int my_strsize(char const *str)
{
    int x = 0;
    while (*str != '\0' ) {
        x++;
        str++;
    }
    return x;
}

char *my_revstr(char *str)
{
    char suite;
    int y = 0;
    int v = my_strsize(str) - 1;
    while (v > y) {
        suite = str[y];
        str[y] = str[v];
        str[v] = suite;
        y = y + 1;
        v = v - 1;
    }
    return str;
}

int *my_revint(int *i, int size)
{
    char suite;
    int y = 0;
    int v = size;
    while (v > y) {
        suite = i[y];
        i[y] = i[v];
        i[v] = suite;
        y = y + 1;
        v = v - 1;
    }
    return i;
}

char *char_tostr(char c)
{
    char *str = malloc(sizeof(char) * 2);
    str[0] = c;
    str[1] = '\0';
    return str;
}