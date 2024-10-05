/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** get_command.c
*/

#include "myteams.h"
#include <unistd.h>
#include <stdlib.h>

static struct d short_opt[] = {
        {"/help", help},
        {"/login", login},
        {"/logout", logout},
        {"/create", creats},
        {"/users", users},
        {"/user", user},
        {"/use", use},
        {"/list", list},
        {"/info", info},
        {"/send", send_getmsg},
        {"/messages", send_getmsg},
        {"/subscribe", subunsub},
        {"/unsubscribe", subunsub},
        {"/subscribed", start_subscribed},
        {NULL, NULL}
};

void siginthandler(int signum)
{
    (void)(signum);
    signalss.sigint_received = false;
}

char **get_cmd(char *cmd)
{
    cmd = my_strip(cmd, "\n", 0);
    cmd = my_strip(cmd, "\r", 0);
    int z = num_args(cmd, "\"", 0, 0);
    if (z % 2 != 0) {
        char **t = malloc(sizeof(*t) * 1);
        t[0] = NULL;
        printf("error in you cmd missing a '\"'");
        return t;
    }
    char **p = my_split(cmd, "\"", 0);
    p = my_pop_twod(p, " ", 0);
    p = my_pop_twod(p, "  ", 0);
    p = my_pop_twod(p, "   ", 0);
    p[0] = my_strip(p[0], " ", 0);
    return p;
}

int start_cmd_sec(my_struct_t *mystruct, int client_sock, char **command, int i)
{
    int code = -10;
    if (strcmp(short_opt[i].cmd, command[0]) == 0) {
        code = short_opt[i].func(mystruct, client_sock, command);
        free_twod(command);
        return code;
    }
    return code;
}

int start_cmd(my_struct_t *mystruct, int client_sock, char *cmd)
{
    int i = get_struct(mystruct->clientstruct, client_sock, "");
    if (cmd == NULL)
        return 84;
    char **command = get_cmd(cmd);
    if (command[0] == NULL)
        return 84;
    cmd = strdup(command[0]);
    if (strcmp("/help", cmd) != 0 && strcmp("/login", cmd)
        != 0 && strcmp("/logout", cmd) != 0
        && mystruct->clientstruct[i]->is_log == false) {
            sendtxt(client_sock, "please login\r\n");
            return 0;
    }
    for (size_t i = 0; short_opt[i].cmd != NULL; i++) {
        int code = start_cmd_sec(mystruct, client_sock, command, i);
        if (code != -10) return code;
    }
    sendtxt(client_sock, "error can't recognize this command!");
    free_twod(command);
    return 0;
}