/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** sub_unsub
*/

#include "myclient.h"

void sub(myclient_t *myteams_client, char **command)
{
    if (my_twod_size(command) < 2) {
        printf("USAGE: /subscribe [“team_uuid”]\n");
        return;
    }
    char *cmd = my_concate_b("%s %s", command[0], command[1]);
    write(myteams_client->fd, cmd, strlen(cmd));
    char *rep = get_command(myteams_client->fd, myteams_client);
    char **t = my_split(strdup(rep), " ", 0);
    command = rm_gui(command);
    if (strcmp(t[0], "!error") == 0) {
        client_error_unknown_team(command[1]);
        return;
    }
    free_twod(t);
    char **split_rep = my_split(rep, "", 0);
    if (my_twod_size(split_rep) < 1) {
        printf("Server error\n");
        return;
    }
    client_print_subscribed(split_rep[0], command[1]);
}

void unsub(myclient_t *myteams_client, char **command)
{
    if (my_twod_size(command) < 2) {
        printf("USAGE: /unsubscribe [“team_uuid”]\n");
        return;
    }
    char *cmd = my_concate_b("%s %s", command[0], command[1]);
    write(myteams_client->fd, cmd, strlen(cmd));
    char *rep = get_command(myteams_client->fd, myteams_client);
    char **t = my_split(strdup(rep), " ", 0);
    command = rm_gui(command);
    if (strcmp(t[0], "!error") == 0) {
        client_error_unknown_team(command[1]);
        return;
    }
    free_twod(t);
    char **split_rep = my_split(rep, "", 0);
    if (my_twod_size(split_rep) < 1) {
        printf("Server error\n");
        return;
    }
    client_print_unsubscribed(split_rep[0], command[1]);
}