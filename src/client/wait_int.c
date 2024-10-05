/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** wait_int
*/

#include "myclient.h"

int set_zero(int sockfd, myclient_t *myteams_client)
{
    FD_ZERO(&myteams_client->readfds);
    FD_SET(sockfd, &myteams_client->readfds);
    FD_SET(STDIN_FILENO, &myteams_client->readfds);
    int maxfd = (sockfd > STDIN_FILENO) ? sockfd : STDIN_FILENO;
    return select(maxfd + 1, &myteams_client->readfds, NULL, NULL, NULL);
}

char **rm_gui(char **command)
{
    for (int i = 0; command[i] != NULL; i++)
        command[i] = my_strip(command[i], "\"", 0);
    return command;
}