/*
** EPITECH PROJECT, 2023
** project
** File description:
** info
*/

#include "myteams.h"

void getchtm(int sockfd, char *path, char *start, char *uuid)
{
    char **k = get_teams(uuid, path, start);
    if (k[0] == NULL) {
        sendtxt(sockfd, my_concate_b("!error %s %s", start, uuid));
        return;
    }
    char **temp;
    char *p = my_concate_b("%s%s.%s.%s", path, start, k[0], k[1]);
    char *buffer = readfile(p);
    if (buffer == NULL) {
        buffer = strdup(my_concate_b("!error %s %s", start, uuid));
    } else {
        temp = my_split(buffer, "\n", 0);
        buffer = my_concate_b("%s%s%s", k[0],  temp[0], k[1]);
        free_twod(temp);
    }
    buffer = my_concate_b("%s\n%s", start, buffer);
    sendtxt(sockfd, buffer);
    free(buffer);
}

void info_sec(my_struct_t *mystruct, int sockfd, int index)
{
    char **temp = malloc(3 * sizeof(char*));
    temp[0] = strdup("/user");
    temp[1] = strdup(mystruct->clientstruct[index]->uuid_str);
    temp[2] = NULL;
    if (mystruct->clientstruct[index]->uuid_team == NULL) {
        user(mystruct, sockfd, temp);
        return;
    } if (mystruct->clientstruct[index]->uuid_chanel == NULL) {
        getchtm(sockfd, TEAMP, "team",
            mystruct->clientstruct[index]->uuid_team);
        return;
    }
    if (mystruct->clientstruct[index]->uuid_thread == NULL) {
        getchtm(sockfd, CHANNELP, "channel",
            mystruct->clientstruct[index]->uuid_chanel);
        return;
    } else if (mystruct->clientstruct[index]->uuid_thread != NULL) {
        getchtm(sockfd, THREADP, "thread",
            mystruct->clientstruct[index]->uuid_thread);
    }
}

int info(my_struct_t *mystruct, int sockfd, char **cmd)
{
    if (my_twod_size(cmd) > 1) {
        sendtxt(sockfd, "help /info\r\n");
        return 84;
    }
    int index = get_struct(mystruct->clientstruct, sockfd, "");
    info_sec(mystruct, sockfd, index);
    return 0;
}