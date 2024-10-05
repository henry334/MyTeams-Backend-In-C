/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** basic_cmd
*/

#include "myteams.h"

int help(my_struct_t *mystruct, int sockfd, char **cmd)
{
    (void)(cmd);
    (void)(mystruct);
    char *b = strdup("casse pas lec\r\n");
    write(sockfd, b, strlen(b));
    free(b);
    return 0;
}

void login_sec(my_struct_t *mystruct, int sockfd, char **cmd, int index)
{
    char **p = get_client(cmd[1], 0);
    if (p[0] == NULL) {
        mystruct->clientstruct[index]->username = strdup(cmd[1]);
        add_client_db(mystruct,
            mystruct->clientstruct[index]->uuid_str, cmd[1]);
        server_event_user_created(
            mystruct->clientstruct[index]->uuid_str, cmd[1]);
    } else {
        free(mystruct->clientstruct[index]->uuid_str);
        mystruct->clientstruct[index]->username = strdup(p[0]);
        mystruct->clientstruct[index]->uuid_str = strdup(p[1]);
        uuid_parse(mystruct->clientstruct[index]->uuid_str,
            mystruct->clientstruct[index]->user_uuid);
    }
    server_event_user_logged_in(mystruct->clientstruct[index]->uuid_str);
    mystruct->clientstruct[index]->is_log = true;
    char *txt = my_concate_b("%s%s",
        mystruct->clientstruct[index]->username,
        mystruct->clientstruct[index]->uuid_str);
    sendtxt(sockfd, txt);
}

int login(my_struct_t *mystruct, int sockfd, char **cmd)
{
    int index = get_struct(mystruct->clientstruct, sockfd, "");
    if (my_twod_size(cmd) < 2) {
        printf("ERROR IN LOGIN\n");
        sendtxt(sockfd, "help /login [\"username\"]\r\n");
        return 84;
    } else if (mystruct->clientstruct[index]->is_log == true) {
        printf("[%d] Already loged in\n", sockfd);
        sendtxt(sockfd, "Already loged in\n");
        return 1;
    }
    char **user = get_user(cmd[1]);
    if (user[1] != NULL) {
        if (is_log(user[1], mystruct) == true) {
            sendtxt(sockfd, "User Already loged in");
            return 84;
        }
    }
    login_sec(mystruct, sockfd, cmd, index);
    return 0;
}

int logout(my_struct_t *mystruct, int sockfd, char **cmd)
{
    (void)(cmd);
    int index = get_struct(mystruct->clientstruct, sockfd, "");
    server_event_user_logged_out(mystruct->clientstruct[index]->uuid_str);
    mystruct->clientstruct = remove_client(mystruct, sockfd);
    close(sockfd);
    FD_CLR(sockfd, &mystruct->server->readfds);
    return 0;
}
