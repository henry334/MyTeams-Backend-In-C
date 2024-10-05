/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** get_command.c
*/

#include "myclient.h"

int get_size(char *cmd)
{
    char **p = my_split(cmd, "\"", 0);
    p = my_pop_twod(p, " ", 0);
    p[0] = my_strip(p[0], " ", 0);
    return my_twod_size(p);
}

bool is_properly_formatted(char *cmd)
{
    int z = num_args(cmd, "\"", 0, 0);
    if (z % 2 != 0) {
        printf("error in you cmd missing a '\"'\n");
        return false;
    }
    return true;
}

char **get_cmd(char *cmd)
{
    bool lock = false;
    bool in_it = false;
    int p = 0;
    char **command = malloc(sizeof(char *) * (get_size(cmd) + 1));
    char *l = strdup("");
    for (int i = 0; cmd[i] != '\0'; i++) {
        l = my_concate_b("%s%c", l, cmd[i]);
        if (in_it == true) free(command[p]);
        command[p] = strdup(l);
        if (cmd[i] == '"') lock = lock == false ? true : false;
        if (cmd[i] == ' ' && lock == false) {
            int k = p;
            in_it = false;
            p = (cmd[i + 1] == '\0' || cmd[i + 1] == ' ') ? p : p + 1;
            l = k == p ? l : strdup("");
        } else
            in_it = true;
        command[p + 1] = NULL;
    }
    return command;
}

char **pass(char *cmd)
{
    if (strlen(my_strip(cmd, " ", 0)) == 0)
        return NULL;
    if (!is_properly_formatted(cmd))
        return NULL;
    char **temp = get_cmd(cmd);
    temp = my_pop_twod(temp, " ", 0);
    temp[0] = my_strip(temp[0], " ", 0);
    return temp;
}

char *get_command(int fd, myclient_t *myteams_client)
{
    char buffer[10240] = {0};
    char *b;
    set_zero(myteams_client->fd, myteams_client);
    if (FD_ISSET(fd, &myteams_client->readfds)) {
        if (read(fd,  buffer, 10240) == 0) {
            logout(myteams_client, NULL);
            exit(0);
        }
    } else {
        if (read(fd,  buffer, 10240) == 0) {
            logout(myteams_client, NULL);
            exit(0);
        }
    }
    b = strdup(buffer);
    return b;
}
