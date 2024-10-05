/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** my_pop_twod
*/

#include "shared.h"

char **my_pop_twod(char **ar, char *topop, int tootakeout)
{
    (void)(tootakeout);
    int num = 0;
    for (int p = 0; ar[p] != NULL; p++) {
        if (strcmp(ar[p], topop) == 0)
            num++;
    }
    char **buff = malloc((my_twod_size(ar) - num + 1) * sizeof(*buff));
    num = 0;
    for (int k = 0; ar[k] != NULL; k++) {
        if (strcmp(ar[k], topop) != 0) {
            buff[num] = ar[k];
            num++;
        }
    }
    buff[num] = NULL;
    return buff;
}

char *my_replace(char *start, char to_replace, char b)
{
    for (int i = 0; start[i] != '\0'; i++) {
        if (start[i] == to_replace) {
            start[i] = b;
        }
    }
    return start;
}