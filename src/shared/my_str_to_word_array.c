/*
** EPITECH PROJECT, 2021
** str_to_word_array
** File description:
** Write a function that splits a string into words
*/

#include "shared.h"

static int check_alpha(char i)
{
    if (i != '\n' && i != '\0' && i != 127 && i != ' ')
        return 1;
    else
        return 0;
}

static int count_word(char const *str)
{
    int i = 0;
    int count = 0;

    while (str[i] != '\0') {
        if (check_alpha(str[i]) == 1 && check_alpha(str[i + 1]) == 0)
            count++;
        i++;
    }
    return count;
}

static int my_strlen_of_word(char const *str, int i)
{
    int count = 0;

    while (str[i] != '\0') {
        if (check_alpha(str[i]) == 1)
            count++;
        else
            return count;
        i++;
    }
    return count;
}

char **my_str_to_word_array(char const *str, int i)
{
    int y = 0;
    int word = count_word(str);
    char **tab = malloc(sizeof(char *) * (word + 1));

    if (tab == NULL)
        return NULL;
    for (int j = 0; j < word; j++) {
        y = 0;
        tab[j] = malloc(sizeof(char) * (my_strlen_of_word(str, i) + 1));
        if (tab[j] == NULL)
            return NULL;
        for (; str[i] != '\0' && check_alpha(str[i]) == 1; i++) {
            tab[j][y] = str[i];
            y++;
        }
        tab[j][y] = '\0';
        i++;
    }
    tab[word] = NULL;
    return tab;
}
