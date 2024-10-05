/*
** EPITECH PROJECT, 2022
** Epitech
** File description:
** code.c
*/

#include "shared.h"

char *my_intchar(long long num)
{
    int new = 0;
    int counter = 0;
    int neg = 1;
    num < 0 ? num = num * -1, neg++ : counter;
    char *list = malloc(sizeof(char) * (my_intlen(num, 10) + neg + 1));
    if (num <= 9) {
        list[counter] = num + '0';
        neg == 2 ? counter++, list[counter] = '-' : neg;
        list[counter + 1] = '\0';
    } else {
        for (; num > 0; counter++) {
            new = num % 10;
            num = num / 10;
            list[counter] = new + '0';
        }
        neg == 2 ? list[counter] = '-', counter++ : neg;
        list[counter] = '\0';
    }
    return my_revstr(list);
}

char *my_simple_conc(char *f, char s, char b)
{
    int c = 0;
    int t = 1;
    b != 127 ? t++ : t;
    char *p = malloc(sizeof(char) * (strlen(f) + 1 + t));
    for (; f[c] != '\0'; c++) {
        p[c] = f[c];
    }
    if (b != 127) {
        p[c] = b;
        c++;
    }
    p[c] = s;
    p[c + 1] = '\0';
    return p;
}

char *my_conc(char *f, char *s, char b)
{
    int c = 0;
    int t = 1;
    b != 127 ? t++ : t;
    char *p = malloc(sizeof(char) * (strlen(f) +
        strlen(s) + t));
    for (; f[c] != '\0'; c++) {
        p[c] = f[c];
    }
    if (b != 127) {
        p[c] = b;
        c++;
    }
    int l = 0;
    int x = c;
    for (; s[l] != '\0'; l++, x++) {
        p[x] = s[l];
    }
    p[x] = '\0';
    return p;
}

char *typess(char p, va_list lists)
{
    if (p == 'c') {
        return char_tostr(va_arg(lists, int));
    }
    if (p == 's') {
        return va_arg(lists, char *);
    } else if (p == 'd') {
        return my_intchar(va_arg(lists, int));
    }
    return "";
}

char *my_concate_b(char *s, ...)
{
    va_list lists;
    va_start(lists, s);
    char *buffer;
    buffer = "";
    int counter = 0;
    for (; s[counter] != '\0' ; counter++) {
        if (s[counter] == '%') {
            counter += 1;
            buffer = my_conc(buffer, typess(s[counter], lists), 127);
        } else
            buffer = my_simple_conc(buffer, s[counter], 127);
    }
    va_end(lists);
    return buffer;
}
