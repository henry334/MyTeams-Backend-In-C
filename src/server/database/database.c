/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** database.c
*/

#include "myteams.h"

char **get_teams(char *find, char *path, char *start)
{
    char **result = malloc(3 * sizeof(char *));
    char **files = readdire(path);
    for (int p = 0; files[p] != NULL; p++) {
        char **t = my_split(files[p], ".", 0);
        if (my_twod_size(t) < 3 || strcmp(t[0], start) != 0)
            continue;
        if (strcmp(t[1], find) == 0 || strcmp(t[2], find) == 0) {
            result[0] = t[1];
            result[1] = t[2];
            result[2] = NULL;
            return result;
        }
    }
    for (int i = 0; i < 3; i++)
        result[i] = NULL;
    return result;
}

char **get_msg(char *sender, char *reciver)
{
    char **result = malloc(2 * sizeof(char *));
    result[0] = strdup("");
    char *files = readfile(MSGP);
    char **lignes;
    if (files != NULL) {
        lignes = my_split(files, "\n", 0);
    }
    for (int p = 0; files != NULL && lignes[p] != NULL; p++) {
        char **t = my_split(lignes[p], "", 0);
        if (my_twod_size(t) < 3)
            continue;
        if ((strcmp(t[0], sender) == 0 && strcmp(t[1], reciver) == 0)
            || (strcmp(t[0], reciver) == 0 && strcmp(t[1], sender) == 0)) {
                result[0] = my_concate_b("%s%s\n", result[0], lignes[p]);
        }
    }
    result[1] = NULL;
    return result;
}

char **get_user(char *find)
{
    char **result = malloc(3 * sizeof(char *));
    for (int i = 0; i < 3; i++)
        result[i] = NULL;
    char *files = readfile(USERP);
    if (files == NULL)
        return result;
    char **lignes = my_split(files, "\n", 0);
    for (int i = 0; lignes[i] != NULL; i++) {
        char **temp = my_split(lignes[i], "", 0);
        if (my_twod_size(temp) < 2)
            continue;
        if (strcmp(temp[0], find) == 0 || strcmp(temp[1], find) == 0) {
            result[0] = strdup(temp[0]);
            result[1] = strdup(temp[1]);
        }
        free_twod(temp);
    }
    free_twod(lignes);
    return result;
}

bool is_sub(char *path, char *uuid)
{
    char *buffer = readfile(path);
    if (buffer == NULL)
        return false;
    char **sectemp = my_split(buffer, "\n", 0);
    for (int i = 0; sectemp[i] != NULL; i++) {
        if (strcmp(sectemp[i], uuid) == 0)
            return true;
    }
    free(buffer);
    free_twod(sectemp);
    return false;
}

int is_log(char *uuid,  my_struct_t *mystruct)
{
    int log = 0;
    int val = get_struct(mystruct->clientstruct, -1, uuid);
    if (val != -1) {
        if (mystruct->clientstruct[val]->is_log == true)
            log = 1;
    }
    return log;
}