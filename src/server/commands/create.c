/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** create
*/

#include "myteams.h"

void creat_team_sec(my_struct_t *mystruct,
    char uuid_str[37], char **cmd, int index)
{
    int sockfd = mystruct->clientstruct[index]->sock_cli;
    char *path =
        malloc(strlen("./src/server/database/teams/team.")
            + strlen(cmd[1]) + strlen(".") + strlen(uuid_str) + 1);
    sprintf(path, "./src/server/database/teams/team.%s.%s", cmd[1], uuid_str);
    char *desc = my_concate_b("team_description%s", cmd[2]);
    writefile(path, "", desc);
    server_event_team_created(uuid_str, cmd[1],
        mystruct->clientstruct[index]->uuid_str);
    free(path);
    char *z = my_concate_b("team %s", uuid_str);
    sendtxt(sockfd, z);
    free(desc);
    free(z);
}

int creat_team(my_struct_t *mystruct, int sockfd, char **cmd, int index)
{
    if (my_twod_size(cmd) < 3) {
        sendtxt(sockfd, "help /create [“name”] [“description”]\r\n");
        return 84;
    }
    if (get_teams(cmd[1], TEAMP, "team")[0] != NULL) {
        sendtxt(sockfd, "?error team existe");
        return 84;
    }
    uuid_t uuid;
    char uuid_str[37];
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    creat_team_sec(mystruct, uuid_str, cmd, index);
    return 0;
}

void create_channel(char *team_uuid, int sockfd, char **cmd)
{
    if (my_twod_size(cmd) < 3) {
        return;
    } else if (get_teams(cmd[1], CHANNELP, "channel")[0] != NULL) {
        sendtxt(sockfd, "?error channel existe");
        return;
    }
    uuid_t uuid;
    char uuid_str[37];
    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    char *path = my_concate_b("%schannel.%s.%s", CHANNELP, cmd[1], uuid_str);
    char *desc = my_concate_b("team_description%s%s", cmd[2], team_uuid);
    writefile(path, "", desc);
    char **k = get_teams(team_uuid, "./src/server/database/teams/", "team");
    if (k[0] == NULL) {
        sendtxt(sockfd, my_concate_b("!error team %s", team_uuid));
        return;
    }
    server_event_channel_created(k[1], uuid_str, cmd[1]);
    sendtxt(sockfd, my_concate_b("channel %s", uuid_str));
}

int creats(my_struct_t *mystruct, int sockfd, char **cmd)
{
    int index = get_struct(mystruct->clientstruct, sockfd, "");
    if (mystruct->clientstruct[index]->uuid_team == NULL)
        return creat_team(mystruct, sockfd, cmd, index);
    if (mystruct->clientstruct[index]->uuid_chanel == NULL) {
        create_channel(mystruct->clientstruct[index]->uuid_team, sockfd, cmd);
        return 0;
    }
    if (mystruct->clientstruct[index]->uuid_thread == NULL) {
        create_thread(mystruct->clientstruct[index]->uuid_chanel,
        mystruct->clientstruct[index]->uuid_str, sockfd, cmd);
        return 0;
    }
    if (mystruct->clientstruct[index]->uuid_thread != NULL) {
        create_threadc(mystruct->clientstruct[index]->uuid_thread,
            mystruct->clientstruct[index]->uuid_str, sockfd, cmd);
    }
    return 0;
}