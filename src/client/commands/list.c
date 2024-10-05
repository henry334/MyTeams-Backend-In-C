/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** list
*/

#include "myclient.h"

void sec_print(char **command, char *type, char **cm, int i)
{
    if (my_twod_size(command) >= 5 && strcmp(type, "team") == 0) {
        client_print_teams(command[2], command[1], command[4]);
    }
    if (my_twod_size(command) >= 6 && strcmp(type, "channels") == 0) {
        client_team_print_channels(command[2], command[1], command[4]);
    }
    if (my_twod_size(command) >= 8 && strcmp(type, "threads") == 0) {
        client_channel_print_threads(command[2],
            command[7], atoi(command[6]), command[1], command[4]);
    }
    if (my_twod_size(command) >= 3 && strcmp(type, "sents") == 0) {
        if (i == 2)
            return;
        client_thread_print_replies(cm[1],
            command[0], atoi(command[2]), command[1]);
    }
}

void print_all(char *type, char **command)
{
    command = rm_gui(command);
    for (int i = 1; command[i] != NULL; i++) {
        char **t = my_split(command[i], "", 0);
        if (my_twod_size(command) >= 3) {
            sec_print(t, type, command, i);
        }
    }
}

void list(myclient_t *myteams_client, char **command)
{
    if (my_twod_size(command) > 1) {
        printf("help /list\n");
        return;
    }
    write(myteams_client->fd, "/list", strlen("/list"));
    char *rep = get_command(myteams_client->fd, myteams_client);
    char **t = my_split(strdup(rep), " ", 0);
    if (strcmp(t[0], "!error") == 0) {
        print_erro(t[1], t[2]);
        return;
    }
    char **temp = my_split(strdup(rep), "\n", 0);
    print_all(temp[0], temp);
}