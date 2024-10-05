/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** list
*/

#include "myteams.h"

int list_all(int sockfd, char *path, char *toskip, char *check)
{
    char **p = readdire(path);
    if (p == NULL) {
        sendtxt(sockfd, my_concate_b("!error %s", check));
        return 84;
    }
    p = my_pop_twod(p, toskip, 0);
    char *start = strdup("");
    for (int i = 0; p[i] != NULL; i++) {
        char *file = readfile(my_concate_b("%s%s", path, p[i]));
        char **wr = my_split(file, "\n", 0);
        if (my_twod_size(wr) < 1)
            continue;
        p[i] = my_replace(p[i], '.', '');
        start = my_concate_b("%s%s%s\n", start, p[i], wr[0]);
    }
    start = my_concate_b("%s\n%s", check, start);
    sendtxt(sockfd, start);
    free(start);
    return 0;
}

void list_replies(myteams_client_t *client, int sockfd)
{
    char **k = get_teams(client->uuid_thread, THREADP, "thread");
    if (k[0] == NULL) {
        sendtxt(sockfd, my_concate_b("!error thread %s", client->uuid_thread));
        return;
    }
    char *path = my_concate_b("%sthread.%s.%s", THREADP, k[0], k[1]);
    char *buffer = readfile(path);
    if (buffer == NULL) {
        buffer = my_concate_b("!error thread %s", client->uuid_thread);
    }
    buffer = my_concate_b("sents\n%s\n%s", client->uuid_thread, buffer);
    sendtxt(sockfd, buffer);
    free(buffer);
    free(path);
}

int list(my_struct_t *mystruct, int sockfd, char **cmd)
{
    if (my_twod_size(cmd) > 1) {
        sendtxt(sockfd, "help /list\r\n");
        return 84;
    }
    int index = get_struct(mystruct->clientstruct, sockfd, "");
    if (mystruct->clientstruct[index]->uuid_team == NULL)
        return list_all(sockfd, TEAMP, "channels", "team");
    if (mystruct->clientstruct[index]->uuid_chanel == NULL)
        return list_all(sockfd, CHANNELP, "threads", "channels");
    if (mystruct->clientstruct[index]->uuid_thread == NULL)
        return list_all(sockfd, THREADP, "", "threads");
    else if (mystruct->clientstruct[index]->uuid_thread != NULL)
        list_replies(mystruct->clientstruct[index], sockfd);
    return 0;
}