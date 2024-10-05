/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** myteams.c
*/

#include "myteams.h"

struct signal_data signalss = {
    .sigint_received = true
};

myteams_serv_t *create_server(int sock_srv)
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock_srv, &readfds);
    myteams_serv_t *server = malloc(sizeof(myteams_serv_t));

    if (server == NULL)
        return NULL;
    server->sock_srv = sock_srv;
    server->readfds = readfds;
    server->max_connect = sock_srv;
    return server;
}

char *get_command(int fd, my_struct_t *mystruct)
{
    (void)(mystruct);
    char buffer[10240] = {0};
    char *b;

    read(fd,  buffer, 10240);
    b = strdup(buffer);
    if (strlen(b) <= 0)
        return NULL;
    return b;
}

void pass(my_struct_t *mystruct, int client_sock)
{
    int c = get_struct(mystruct->clientstruct, client_sock, "");
    if (c == -1) {
        return;
    }
    char *cmd = get_command(client_sock, mystruct);
    if (cmd == NULL)
        return;
    start_cmd(mystruct, client_sock, cmd);
}

void sec_list(int sockfd, my_struct_t *mystruct)
{
    fd_set tmp_fds = mystruct->server->readfds;
    int nready =
        select(mystruct->server->max_connect + 1,
            &tmp_fds, NULL, NULL, NULL);
    if (nready < 0)
        return;
    for (int c = 0; c <= mystruct->server->max_connect; c++) {
        if (FD_ISSET(c, &tmp_fds)) {
            c == sockfd ?
            handle_client(mystruct->server, mystruct)
                : pass(mystruct, c);
        }
    }
}

void server_listenning(int sockfd)
{
    my_struct_t mystruct = init_mystruct();
    mystruct.server = create_server(sockfd);
    signal(SIGINT, &siginthandler);
    while (signalss.sigint_received) {
        sec_list(sockfd, &mystruct);
    }
    kill_all_cli(mystruct.clientstruct);
    free_client(mystruct.clientstruct);
    close(sockfd);
}
