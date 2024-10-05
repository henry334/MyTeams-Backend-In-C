/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** error.c
*/

#include "myteams.h"

void error_handling(char *str)
{
    perror(str);
    exit(84);
}

int check_error_creating(void)
{
    int sock_srv = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_srv < 0)
        return error_handling("socket(): "), -1;
    int optval = 1;
    setsockopt(sock_srv, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    return sock_srv;
}
