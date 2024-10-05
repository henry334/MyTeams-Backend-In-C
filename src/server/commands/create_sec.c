/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** create_sec
*/

#include "myteams.h"

void create_sec(char *c_u, char *user_d, int sockfd, char **cmd)
{
    uuid_t uuid;
    char uuid_str[37];
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    char *path = my_concate_b("%sthread.%s.%s", THREADP, cmd[1], uuid_str);
    time_t current_time;
    char tm[20];
    current_time = time(NULL);
    sprintf(tm, "%ld", (long)current_time);
    char *desc = my_concate_b("thread_description%s%s%s%s",
        cmd[2], c_u, strdup(tm), user_d);
    writefile(path, "", desc);
    char **k = get_teams(c_u, CHANNELP, "channel");
    if (k[0] == NULL) {
        sendtxt(sockfd, my_concate_b("!error channel %s", c_u));
        return;
    }
    server_event_thread_created(c_u, uuid_str, user_d, cmd[1], cmd[2]);
    sendtxt(sockfd, my_concate_b("thread %s %s", uuid_str, user_d));
}

void create_thread(char *c_u, char *user_d, int sockfd, char **cmd)
{
    if (my_twod_size(cmd) < 3) {
        return;
    } else if (get_teams(cmd[1], THREADP, "thread")[0] != NULL) {
        sendtxt(sockfd, "?error thread existe");
        return;
    }
    create_sec(c_u, user_d, sockfd, cmd);
}