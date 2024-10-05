/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** unsubsub
*/

#include "myteams.h"

void subscribe(my_struct_t *mystruct, int sockfd, char **cmd, int index)
{
    char **temp = get_teams(cmd[1], TEAMP, "team");
    if (temp[0] == NULL) {
        sendtxt(sockfd, "!error team_uuid dont existe\r\n");
        return;
    }
    char *path = my_concate_b("%steam.%s.%s", TEAMP, temp[0], temp[1]);
    char *buffer = readfile(path);
    if (strlen(buffer) != 0)
        buffer = my_concate_b("%s\n", buffer);
    writefile(path, buffer, mystruct->clientstruct[index]->uuid_str);
    sendtxt(sockfd, mystruct->clientstruct[index]->uuid_str);
    server_event_user_subscribed(
        temp[1], mystruct->clientstruct[index]->uuid_str);
    free(path);
    free(buffer);
    free_twod(temp);
}

void unsubscribe(my_struct_t *mystruct, int sockfd, char **cmd, int index)
{
    char **temp = get_teams(cmd[1], TEAMP, "team");
    if (temp[0] == NULL) {
        sendtxt(sockfd, "!error team_uuid dont existe\r\n");
        return;
    }
    char *newfile = strdup("");
    char *path = my_concate_b("%steam.%s.%s", TEAMP, temp[0], temp[1]);
    char *buffer = readfile(path);
    char **sectemp = my_split(buffer, "\n", 0);
    for (int i = 0; sectemp[i] != NULL; i++) {
        if (strcmp(sectemp[i], mystruct->clientstruct[index]->uuid_str) != 0)
            newfile = my_concate_b("%s%s\n", newfile, sectemp[i]);
    }
    writefile(path, "", newfile);
    sendtxt(sockfd, mystruct->clientstruct[index]->uuid_str);
    server_event_user_unsubscribed(
        temp[1], mystruct->clientstruct[index]->uuid_str);
    free(path);
    free(buffer);
    free_twod(temp);
}

int subunsub(my_struct_t *mystruct, int sockfd, char **cmd)
{
    if (my_twod_size(cmd) > 2) {
        sendtxt(sockfd, my_concate_b("help %s [“team_uuid”]\r\n", cmd[0]));
        return 84;
    }
    int index = get_struct(mystruct->clientstruct, sockfd, "");
    if (strcmp(cmd[0], "/subscribe") == 0) {
        subscribe(mystruct, sockfd, cmd, index);
    } else if (strcmp(cmd[0], "/unsubscribe") == 0) {
        unsubscribe(mystruct, sockfd, cmd, index);
    }
    return 0;
}