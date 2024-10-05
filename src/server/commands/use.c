/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** use
*/

#include "myteams.h"

int set_uuid(myteams_client_t *clientstruct,
    char *team, char *chanel, char *thread)
{
    clientstruct->uuid_thread = NULL;
    clientstruct->uuid_team = NULL;
    clientstruct->uuid_chanel = NULL;
    if (thread != NULL)
        clientstruct->uuid_thread = strdup(thread);
    if (team != NULL)
        clientstruct->uuid_team = strdup(team);
    if (chanel != NULL)
        clientstruct->uuid_chanel = strdup(chanel);
    return 1;
}

int use(my_struct_t *mystruct, int sockfd, char **cmd)
{
    int p = 0;
    int val = get_struct(mystruct->clientstruct, sockfd, "");
    if (my_twod_size(cmd) == 1)
        p = set_uuid(mystruct->clientstruct[val], NULL, NULL, NULL);
    if (my_twod_size(cmd) == 2)
        p = set_uuid(mystruct->clientstruct[val], cmd[1], NULL, NULL);
    if (my_twod_size(cmd) == 3)
        p = set_uuid(mystruct->clientstruct[val], cmd[1], cmd[2], NULL);
    if (my_twod_size(cmd) == 4)
        p = set_uuid(mystruct->clientstruct[val], cmd[1], cmd[2], cmd[3]);
    if (p == 1)
        sendtxt(sockfd, "OK");
    else
        sendtxt(sockfd, "KO");
    return 0;
}