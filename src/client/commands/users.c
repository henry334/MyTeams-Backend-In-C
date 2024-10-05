/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** users.c
*/

#include "myclient.h"

void users(myclient_t *myteams_client, char **command)
{
    (void)command;
    write(myteams_client->fd, command[0], strlen(command[0]));
    char *rep = get_command(myteams_client->fd, myteams_client);
    char **temp = my_split(strdup(rep), " ", 0);
    if (strcmp(temp[0], "!error") == 0) {
        printf("No users\n");
        return;
    }
    char **split_rep = my_split(rep, "\n", 0);
    for (int i = 0; split_rep[i] != NULL; i++) {
        char **sect = my_split(split_rep[i], "", 0);
        if (my_twod_size(sect) < 3)
            continue;
        client_print_users(sect[1], sect[0], atoi(sect[2]));
    }
    free_twod(split_rep);
}

void user(myclient_t *myteams_client, char **command)
{
    if (my_twod_size(command) < 2) {
        printf("/user [user_uuid]\n");
        return;
    }
    char *cmd = my_concate_b("%s %s", command[0], command[1]);
    write(myteams_client->fd, cmd, strlen(cmd));
    char *rep = get_command(myteams_client->fd, myteams_client);
    rep = my_strip(rep, "\n", 0);
    char **temp = my_split(strdup(rep), " ", 0);
    if (strcmp(temp[0], "!error") == 0) {
        client_error_unknown_user(command[1]);
    }
    free_twod(temp);
    temp = my_split(rep, "", 0);
    if (my_twod_size(temp) >= 3)
        client_print_user(temp[1], temp[0], atoi(temp[2]));
}