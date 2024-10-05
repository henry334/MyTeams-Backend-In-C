/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** info
*/

#include "myclient.h"

void print_user(char *cmd)
{
    char **temp = my_split(cmd, "", 0);
    if (my_twod_size(temp) != 3)
        return;
    client_print_user(temp[1], temp[0] , atoi(temp[2]));
}

void print_rst(char *cmd, char *type)
{
    char **temp = my_split(cmd, "", 0);
    if (my_twod_size(temp) < 5)
        return;
    if (strcmp(type, "team") == 0) {
        client_print_team(temp[3], temp[0], temp[2]);
    }
    if (strcmp(type, "channel") == 0) {
        client_print_channel(temp[3], temp[0], temp[2]);
    }
    if (my_twod_size(temp) > 6 && strcmp(type, "thread") == 0) {
        client_print_thread(temp[3], temp[5], atoi(temp[4]), temp[0], temp[2]);
    }
}

void info(myclient_t *myteams_client, char **command)
{
    if (my_twod_size(command) > 1) {
        printf("help /info\n");
        return;
    }
    write(myteams_client->fd, "/info", strlen("/info"));
    char *rep = get_command(myteams_client->fd, myteams_client);
    char **t = my_split(strdup(rep), " ", 0);
    if (strcmp(t[0], "!error") == 0) {
        print_erro(t[1], t[2]);
        return;
    }
    char **temp = my_split(rep, "\n", 0);
    if (my_twod_size(temp) == 1)
        print_user(temp[0]);
    print_rst(temp[1], temp[0]);
    return;
}