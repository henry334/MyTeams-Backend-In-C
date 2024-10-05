/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** help.c
*/

#include "myclient.h"

void help(myclient_t *client, char **command)
{
    (void)client;
    (void)command;
    printf("USAGE: ./myteams_cli ip port\n");
    printf(
    "\tip is the server ip address on which the server socket listens\n");
    printf("\tport is the port number on which the server socket listens\n");
}