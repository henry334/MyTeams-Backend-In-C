/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** send_msg
*/

#include "myclient.h"

void sendmsges(myclient_t *myteams_client, char **command)
{
    if (my_twod_size(command) < 3) {
        printf("USAGE: /send [user_uuid] [message_body]\n");
        return;
    }
    char *cmd = my_concate_b("%s %s %s", command[0], command[1], command[2]);
    write(myteams_client->fd, cmd, strlen(cmd));
    char *rep = get_command(myteams_client->fd, myteams_client);
    rep = my_strip(rep, "\n", 0);
    char **temp = my_split(strdup(rep), " ", 0);
    if (strcmp(temp[0], "!error") == 0) {
        client_error_unknown_user(rm_gui(command)[1]);
    } else {
        printf("%s\n", rep);
    }
    free(rep);
    free_twod(temp);
}

void messages(myclient_t *myteams_client, char **command)
{
    if (my_twod_size(command) < 2) {
        printf("USAGE: /messages [user_uuid]\n");
        return;
    }
    char *cmd = my_concate_b("%s %s", command[0], command[1]);
    write(myteams_client->fd, cmd, strlen(cmd));
    char *rep = get_command(myteams_client->fd, myteams_client);
    char **t = my_split(strdup(rep), " ", 0);
    if (strcmp(t[0], "!error") == 0) {
        client_error_unknown_user(rm_gui(command)[1]);
        return;
    } else if (strcmp(t[0], "#error") == 0)
        return;
    char **temp = my_split(strdup(rep), "\n", 0);
    for (int i = 0; temp[i] != NULL; i++) {
        char **sect = my_split(temp[i], "", 0);
        if (my_twod_size(sect) < 3)
            continue;
        client_private_message_print_messages(sect[0], 0, sect[2]);
    }
}