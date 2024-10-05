/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** shared
*/

#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void free_twod(char **tofree);
int my_twod_size(char **temp);
char **my_str_to_word_array(char const *str, int i);
char **my_split(char *argv, char *parse, int t);
char *add(char *string, int start, int max);
int size_arg(char *argv, int where, char *parse, int t);
int num_args(char *argv, char *parse, int t, int c);
char *my_strip(char *string, char *parse, int num);
int my_check(char *parse, int where, char *string);
char *my_concate_b(char *s, ...);
int my_intlen(long long number, int div);
char *my_revstr(char *str);
char **my_pop_twod(char **ar, char *topop, int max);
char *my_replace(char *start, char to_replace, char b);
char *char_tostr(char c);