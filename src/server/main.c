/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** main.c
*/

#include "myteams.h"

int run_teams(char **av)
{
    (void)(av);
    int sock_srv = 0;

    if ((sock_srv = check_error_creating()) == -1)
        return -1;

    printf("Socket created\n");
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(av[1]));
    if (bind(sock_srv, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error_handling("bind(): ");
    if (listen(sock_srv, 15) < 0)
        error_handling("listen(): ");
    server_listenning(sock_srv);
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 2) {
        print_help();
        return 84;
    } else if (strcmp(av[1], "-help") == 0)
        print_help();
    else
        run_teams(av);
    return 0;
}