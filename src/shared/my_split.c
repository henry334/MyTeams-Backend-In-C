/*
** EPITECH PROJECT, 2022
** Epitech
** File description:
** code.c
*/

#include "shared.h"

int my_check(char *parse, int where, char *string)
{
    int c;
    for (c = 0; parse[c] != '\0'; c++, where++) {
        if (parse[c] != string[where])
            return -1;
    }
    return c;
}

int num_args(char *argv, char *parse, int t, int c)
{
    int num = 0;
    int lock;

    for (; argv[c] != '\0'; c++) {
        lock = my_check(parse, c, argv);
        lock != -1 ? t-- : t;
        if (t < 0 && lock != -1) {
            num++;
            c = lock + c - 1;
        }
    }
    return num;
}

int size_arg(char *argv, int where, char *parse, int t)
{
    int num = 0;
    int br = 0;
    int size = strlen(parse);
    for (; argv[where] != '\0'; where++, num++) {
        for (int c = 0; c < size && argv[where + c] != '\0'; c++) {
            argv[where + c] != parse[c] ? br = 0 : br++;
        }
        br >= size ? t-- : t;
        if (br >= size && t < 0)
            break;
    }
    return num;
}

char *add(char *string, int start, int max)
{
    int l = 0;
    char *temp = malloc(sizeof(char) * (max + 1));
    for (; l < max; start++, l++) {
        temp[l] = string[start];
    }
    temp[l] = '\0';
    return temp;
}

char **my_split(char *argv, char *parse, int t)
{
    int row = 0;
    char **buff = malloc((num_args(argv, parse, t, 0) + 3) * sizeof(*buff));
    for (size_t c = 0; c < strlen(argv); c++) {
        int lock = my_check(parse, c, argv);
        if (t <= 0 && lock != -1) {
            c = c + lock - 1;
        } else {
            int i = size_arg(argv, c, parse, t);
            buff[row] = add(argv, c, i);
            c = c + i - 1;
            row = row + 1;
            t = 0;
        }
    }
    buff[row] = NULL;
    return buff;
}
