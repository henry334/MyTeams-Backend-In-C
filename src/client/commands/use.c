/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** use.c
*/

#include "myclient.h"

char *concat_msg(char **command)
{
    char *space = strdup(" ");
    char *cmd = strdup("");
    for (int i = 0; command[i] != NULL; i++) {
        if (i == 1)
            space = strdup(" ");
        cmd = my_concate_b("%s%s%s", cmd, space, command[i]);
        if (command[i + 1] == NULL)
            space = strdup("");
    }
    return cmd;
}

void use(myclient_t *myteams_client, char **command)
{
    char *cmd = NULL;
    char *rep = NULL;

    cmd = concat_msg(command);
    write(myteams_client->fd, cmd, strlen(cmd));
    rep = get_command(myteams_client->fd, myteams_client);
    if (strcmp(rep, "KO") == 0) {
        printf("Error /use");
        return;
    }
    free(rep);
}