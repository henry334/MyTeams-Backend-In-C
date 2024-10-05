/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** create
*/

#include "myclient.h"

void print_erro(char *error, char *uuid)
{
    if (strcmp(error, "team") == 0) {
        client_error_unknown_team(uuid);
    }
    if (strcmp(error, "channel") == 0) {
        client_error_unknown_channel(uuid);
    }
    if (strcmp(error, "thread") == 0) {
        client_error_unknown_thread(uuid);
    }
}

void print_success(char **t, char **cmd, time_t time)
{
    if (strcmp(t[0], "team") == 0) {
        client_print_team_created(t[1], cmd[1], cmd[2]);
    }
    if (strcmp(t[0], "channel") == 0) {
        client_print_channel_created(t[1], cmd[1], cmd[2]);
    }
    if (strcmp(t[0], "thread") == 0) {
        client_print_thread_created(t[1], t[2], time, cmd[1], cmd[2]);
    }
    if (strcmp(t[0], "sent") == 0) {
        client_print_reply_created(t[1], t[2], time, cmd[1]);
    }
}

void create(myclient_t *myteams_client, char **command)
{
    (void)(myteams_client);
    if (my_twod_size(command) > 5) {
        printf("USAGE: /create ?[“...”] ?[“...”] \n");
        return;
    }
    char *cmd = concat_msg(command);
    write(myteams_client->fd, cmd, strlen(cmd));
    time_t current_time;
    time(&current_time);
    char *rep = get_command(myteams_client->fd, myteams_client);
    char **t = my_split(strdup(rep), " ", 0);
    if (strcmp(t[0], "!error") == 0) {
        print_erro(t[1], t[2]);
        return;
    } else if (strcmp(t[0], "?error") == 0) {
        client_error_already_exist();
        return;
    }
    command = rm_gui(command);
    print_success(t, command, current_time);
}