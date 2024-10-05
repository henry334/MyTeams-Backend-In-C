/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** login.c
*/

#include "myclient.h"

void login(myclient_t *myteams_client, char **command)
{
    if (command[1] == NULL) {
        printf("USAGE: /login [username]\n");
        return;
    }
    char *cmd = my_concate_b("%s %s", command[0], command[1]);
    write(myteams_client->fd, cmd, strlen(cmd));
    char *rep = get_command(myteams_client->fd, myteams_client);
    rep = my_strip(rep, "\n", 0);
    char **split_rep = my_split(rep, "", 0);
    if (my_twod_size(split_rep) < 2)
        return;
    myteams_client->user_name = strdup(split_rep[0]);
    myteams_client->user_uuid = strdup(split_rep[1]);
    client_event_logged_in(split_rep[1], split_rep[0]);
    free(rep);
    free_twod(split_rep);
    myteams_client->login = true;
}

void logout(myclient_t *myteams_client, char **command)
{
    if (myteams_client->login == false)
        return;
    (void)command;
    write(myteams_client->fd, "/logout", strlen("/logout"));
    myteams_client->exit = true;
    myteams_client->login = false;
    client_event_logged_out(
        myteams_client->user_uuid, myteams_client->user_name);
}
