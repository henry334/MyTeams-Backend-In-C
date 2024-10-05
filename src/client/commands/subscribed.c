/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** subscribed
*/

#include "myclient.h"

void subscribed_size_one(char *rep)
{
    char **sect = NULL;
    char **split_rep = my_split(rep, "\n", 0);
    for (int i = 0; split_rep[i] != NULL; i++) {
        sect = my_split(split_rep[i], "", 0);
        if (my_twod_size(sect) < 3)
            continue;
        client_print_teams(sect[1], sect[0], sect[2]);
    }
    free_twod(split_rep);
}

void subscribed_size_two(char *rep)
{
    char **sect = NULL;
    char **split_rep = my_split(rep, "\n", 0);
    for (int i = 0; split_rep[i] != NULL; i++) {
        sect = my_split(split_rep[i], "", 0);
        if (my_twod_size(sect) < 3)
            continue;
        client_print_users(sect[1], sect[0], atoi(sect[2]));
    }
    free_twod(split_rep);
    return;
}

void subed(myclient_t *myteams_client, char **command)
{
    if (my_twod_size(command) < 1) {
        printf("USAGE: /subscribed [“team_uuid”]\n");
        return;
    }
    char *cmd = strdup("/subscribed");
    if (my_twod_size(command) == 2)
        cmd = my_concate_b("%s %s", command[0], command[1]);
    write(myteams_client->fd, cmd, strlen(cmd));
    char *rep = get_command(myteams_client->fd, myteams_client);
    if (strlen(rep) == 0)
        return;
    char **t = my_split(strdup(rep), " ", 0);
    if (strcmp(t[0], "!error") == 0) {
        client_error_unknown_team(rm_gui(command)[1]);
        return;
    }
    if (my_twod_size(command) == 1) {
        subscribed_size_one(rep);
    } else if (my_twod_size(command) == 2)
        subscribed_size_two(rep);
}
