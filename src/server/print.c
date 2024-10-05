/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** print.c
*/

#include "myteams.h"

void print_help(void)
{
    printf("USAGE: ./myteams_server port\n\tport is the port number on "
        "which the server socket listens.\n");
}

int	send_message(int fd, int code, const char *message)
{
    if (code < 0)
        return (dprintf(fd, "%s\n", message));
    return (dprintf(fd, "%d %s\r\n", code, message));
}
