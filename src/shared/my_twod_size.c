/*
** EPITECH PROJECT, 2022
** Epitech
** File description:
** code.c
*/

#include "shared.h"

int my_twod_size(char **temp)
{
    int c = 0;
    if (temp == NULL)
        return c;
    while (temp[c] != NULL) {
        c++;
    }
    return c;
}

void free_twod(char **tofree)
{
    if (tofree == NULL)
        return;
    for (int i = 0; tofree[i] != NULL; i++) {
        free(tofree[i]);
    }
    free(tofree);
}