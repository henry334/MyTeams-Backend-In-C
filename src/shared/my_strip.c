/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** code.c
*/

#include "shared.h"

char *my_strip(char *string, char *parse, int num)
{
    int c = 0;
    int t = 0;
    int lock;
    int max = 1;
    strlen(parse) == 1 ? max++ : max;
    char *new = malloc(sizeof(char) *
        (strlen(string) - num_args(string, parse, 0, 0) + max + num));
    for (; string[t] != '\0'; t++) {
        lock = my_check(parse, t, string);
        lock != - 1 ? num-- : num;
        if (lock != -1 && num < 0) {
            t = t + lock - 1;
        } else {
            new[c] = string[t];
            c++;
        }
    }
    new[c] = '\0';
    return new;
}
