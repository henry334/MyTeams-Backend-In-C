/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** users
*/

#include "myteams.h"

int users(my_struct_t *mystruct, int sockfd, char **cmd)
{
    if (my_twod_size(cmd) > 1) {
        sendtxt(sockfd, "help /users\r\n");
        return 84;
    }
    char *buffer = readfile(USERP);
    if (buffer == NULL) {
        sendtxt(sockfd, "!error no user\r\n");
        return 0;
    }
    char *txt = strdup("");
    char **users = my_split(buffer, "\n", 0);
    for (int i = 0; users[i] != NULL; i++) {
        char **tp = my_split(users[i], "", 0);
        txt = my_concate_b("%s%s%d\n",
            txt, users[i], is_log(tp[0], mystruct));
    }
    sendtxt(sockfd, txt);
    free(buffer);
    return 0;
}

int user_sec(char **temp, my_struct_t *mystruct, int sockfd)
{
    int log = is_log(temp[0], mystruct);
    char *txt = malloc(sizeof(char) *
        (strlen(temp[0]) + strlen(temp[1]) + 31));
    sprintf(txt, "%s%s%d\r\n", temp[0], temp[1], log);
    sendtxt(sockfd, txt);
    free_twod(temp);
    free(txt);
    return 0;
}

int user(my_struct_t *mystruct, int sockfd, char **cmd)
{
    if (my_twod_size(cmd) < 2) {
        sendtxt(sockfd, "help /user [“user_uuid”]\r\n");
        return 84;
    }
    char *buffer = readfile(USERP);
    if (buffer == NULL) {
        sendtxt(sockfd, "!error no users\r\n");
        return 0;
    }
    char **users = my_split(buffer, "\n", 0);
    for (int i = 0; users[i] != NULL; i++) {
        char **temp = my_split(users[i], "", 0);
        if (my_twod_size(temp) < 2) continue;
        if (strcmp(cmd[1], temp[1]) == 0)
            return user_sec(temp, mystruct, sockfd);
        free_twod(temp);
    }
    sendtxt(sockfd, "error unkown user\r\n");
    return 0;
}