/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** subscribed
*/

#include "myteams.h"

char **all_user_sub(char *path)
{
    char *buff = readfile(path);
    if (buff == NULL)
        return NULL;
    char **temp = my_split(buff, "\n", 0);
    free(buff);
    return temp;
}

char *sub_user_sec(char *ligne, my_struct_t *mystruct)
{
    char *lg = strdup("");
    int log = 0;
    int val = get_struct(mystruct->clientstruct, -1, ligne);
    if (val != -1) {
        if (mystruct->clientstruct[val]->is_log == true)
            log = 1;
    }
    char **temp = get_user(ligne);
    if (temp[0] != NULL) {
        lg = my_concate_b("%s%s%d", temp[0], temp[1], log);
    }
    free_twod(temp);
    return lg;
}

void subscribed_user(my_struct_t *mystruct, int sockfd, char **cmd)
{
    char *lgns = strdup("");
    char **temp = get_teams(cmd[1], TEAMP, "team");
    if (temp[0] == NULL) {
        sendtxt(sockfd, "!error team uuid dont existe\r\n");
        return;
    }
    char *path = my_concate_b("%steam.%s.%s", TEAMP, temp[0], cmd[1]);
    free_twod(temp);
    temp = all_user_sub(path);
    for (int i = 1; temp[i] != NULL; i++) {
        char *l = sub_user_sec(temp[i], mystruct);
        lgns = my_concate_b("%s%s\n", lgns, l);
        free(l);
    }
    sendtxt(sockfd, lgns);
    free(lgns);
    free_twod(temp);
}

void subscribed_team(my_struct_t *mystruct, int sockfd, int index)
{
    char *sub = strdup("");
    char **p = readdire(TEAMP);
    for (int i = 0; p[i] != NULL; i++) {
        char **arg = my_split(p[i], ".", 0);
        char *path = my_concate_b("%s%s", TEAMP, p[i]);
        bool val = is_sub(path, mystruct->clientstruct[index]->uuid_str);
        if (val != true)
            continue;
        char **temp = all_user_sub(path);
        temp = my_split(temp[0], "", 0);
        if (my_twod_size(arg) < 3 || my_twod_size(temp) < 2)
            continue;
        char *buff = my_concate_b("%s%s%s", arg[1], arg[2], temp[1]);
        sub = my_concate_b("%s%s\n", sub, buff);
        free(buff);
        free_twod(temp);
        free(path);
    }
    sendtxt(sockfd, sub);
}

int start_subscribed(my_struct_t *mystruct, int sockfd, char **cmd)
{
    if (my_twod_size(cmd) > 2) {
        sendtxt(sockfd, "help /subscribed [“team_uuid”]\r\n");
        return 84;
    }
    int index = get_struct(mystruct->clientstruct, sockfd, "");
    if (my_twod_size(cmd) > 1)
        subscribed_user(mystruct, sockfd, cmd);
    else
        subscribed_team(mystruct, sockfd, index);
    return 0;
}