/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** message
*/

#include "myteams.h"

void create_threadc(char *thread_uuid, char *user_uuid, int sockfd, char **cmd)
{
    if (my_twod_size(cmd) < 2)
        return;
    char **k = get_teams(thread_uuid, THREADP, "thread");
    if (k[0] == NULL) {
        sendtxt(sockfd, my_concate_b("!error thread %s", thread_uuid));
        return;
    }
    time_t current_time;
    char tm[20];
    current_time = time(NULL);
    sprintf(tm, "%ld", (long)current_time);
    char *path = my_concate_b("%s/thread.%s.%s", THREADP, k[0], thread_uuid);
    char *desc = my_concate_b("%s%s%s", user_uuid, cmd[1], strdup(tm));
    char *start = strdup("");
    char *z = readfile(path);
    if (z != NULL)
        start = my_concate_b("%s\n", strdup(z));
    writefile(path, start, desc);
    server_event_reply_created(thread_uuid, user_uuid, cmd[1]);
    sendtxt(sockfd, my_concate_b("sent %s %s", thread_uuid, user_uuid));
}

void sendmesg(my_struct_t *mystruct, int sockfd, char **cmd)
{
    if (my_twod_size(cmd) < 3) {
        sendtxt(sockfd, "help /send [“user_uuid”] [“message_body”]\r\n");
        return;
    }
    int index = get_struct(mystruct->clientstruct, sockfd, "");
    char *buffer = readfile(MSGP);
    if (buffer == NULL) {
        buffer = strdup("");
    } else
        buffer = my_concate_b("%s\n", buffer);
    char *msg = my_concate_b("%s%s%s",
        mystruct->clientstruct[index]->uuid_str, cmd[1], cmd[2]);
    writefile(MSGP, buffer, msg);
    server_event_private_message_sended(
        mystruct->clientstruct[index]->uuid_str, cmd[1], cmd[2]);
    sendtxt(sockfd, "msg sent");
    free(buffer);
}

void message(char *user_uuid, int sockfd, char **cmd)
{
    if (my_twod_size(cmd) < 2) {
        sendtxt(sockfd, "help /send [“user_uuid”] [“message_body”]\r\n");
        return;
    }
    char **temp = get_msg(user_uuid, cmd[1]);
    if (strlen(temp[0]) == 0) {
        sendtxt(sockfd, "#error no conversation");
        return;
    }
    temp[0] = my_concate_b("%s", temp[0]);
    sendtxt(sockfd, temp[0]);
    free_twod(temp);
    return;
}

int send_getmsg(my_struct_t *mystruct, int sockfd, char **cmd)
{
    int index = get_struct(mystruct->clientstruct, sockfd, "");
    if (my_twod_size(cmd) < 2) {
        return 84;
    }
    if (get_client(cmd[1], 1)[0] == NULL) {
        sendtxt(sockfd, "!error “user_uuid” dont existe\r\n");
        return 84;
    }
    if (strcmp(cmd[0], "/send") == 0) {
        sendmesg(mystruct, sockfd, cmd);
    } else if (strcmp(cmd[0], "/messages") == 0) {
        message(mystruct->clientstruct[index]->uuid_str , sockfd, cmd);
    }
    return 0;
}