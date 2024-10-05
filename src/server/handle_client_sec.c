/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** handle_client_sec
*/

#include "myteams.h"

void free_client(myteams_client_t **tofree)
{
    for (int i = 0; tofree[i] != NULL; i++) {
        free(tofree[i]);
    }
    free(tofree);
}

void handle_client(myteams_serv_t *server, my_struct_t *mystruct)
{
    int client_sock;
    struct sockaddr_in clientt;
    socklen_t cli_len = sizeof(clientt);
    client_sock =
        accept(server->sock_srv, (struct sockaddr *)&clientt, &cli_len);
    if (client_sock < 0)
        return error_handling("accept(): ");
    add_client(mystruct, client_sock);
    FD_SET(client_sock, &server->readfds);
    server->max_connect =
        client_sock > server->sock_srv ? client_sock : server->max_connect;
}

int add_client_db(my_struct_t *mystruct, char *uuid_str, char *name)
{
    (void)(mystruct);
    char *c = strdup("");
    char *start = readfile(USERP);
    if (start == NULL) {
        start = strdup("");
        c = strdup("");
    } else
        start = my_concate_b("%s\n", start);
    char *end = malloc(sizeof(char)
        * (strlen(uuid_str) + strlen(uuid_str) + 1));
    sprintf(end, "%s%s%s", c, name, uuid_str);
    writefile(USERP, start, end);
    return 0;
}

char **get_client(char *match, int index)
{
    char **p = malloc(sizeof(char *));
    p[0] = NULL;
    char *start = readfile(USERP);
    if (start == NULL)
        return p;
    char **t = my_split(start, "\n", 0);
    for (int i = 0; t[i] != NULL; i++) {
        char **temp = my_split(t[i], "", 0);
        if (strcmp(temp[index], match) == 0) {
            p = realloc(p, sizeof(char *) * 3);
            p[0] = strdup(temp[0]);
            p[1] = strdup(temp[1]);
            p[2] = NULL;
            return p;
        }
    }
    return p;
}

void kill_all_cli(myteams_client_t **clientstruct)
{
    for (int i = 0; clientstruct[i] != NULL; i++) {
        close(clientstruct[i]->sock_cli);
    }
}