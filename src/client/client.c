/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** client.c
*/

#include "myclient.h"

volatile bool stop = true;

void siginthandler(int sig)
{
    (void)(sig);
    close(STDIN_FILENO);
    printf("\n");
    stop = false;
}

void sec_loop(myclient_t *myteams_client)
{
    size_t len = 0;
    char *buffer = NULL;
    if (getline(&buffer, &len, stdin) == EOF) {
        logout(myteams_client, NULL);
        exit(0);
    }
    if (strlen(buffer) == 0 || buffer[0] == '\n'
        || strcmp(buffer, "error") == 0) return;
    char *temp = my_strip(strdup(buffer), "\n", 0);
    char **command = pass(strdup(temp));
    exect_command(myteams_client, command);
    free(temp);
    free_twod(command);
}

void client_loop(myclient_t *myteams_client)
{
    signal(SIGINT, &siginthandler);
    while (stop) {
        set_zero(myteams_client->fd, myteams_client);
        if (FD_ISSET(STDIN_FILENO, &myteams_client->readfds)) {
            sec_loop(myteams_client);
        } else
            get_command(myteams_client->fd, myteams_client);
        if (myteams_client->exit == true)
            break;
    }
    logout(myteams_client, NULL);
}

myclient_t *create_client(int sock, char *ip, int port)
{
    myclient_t *myteams_client = malloc(sizeof(myclient_t));
    if (myteams_client == NULL)
        return NULL;
    myteams_client->fd = sock;
    myteams_client->ip = ip;
    myteams_client->port = port;
    myteams_client->exit = false;
    myteams_client->login = false;
    return myteams_client;
}

void run_client(char **av)
{
    int sock = 0;
    myclient_t *myteams_client;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_handling("socket(): ");
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(av[2]));
    if (inet_pton(AF_INET, av[1], &serv_addr.sin_addr) <= 0)
        error_handling("inet():");
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error_handling("connect(): ");
    if ((myteams_client = create_client(sock, av[1], atoi(av[2]))) == NULL)
        error_handling("create_client(): ");
    client_loop(myteams_client);
}
