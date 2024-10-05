/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** command_sec
*/

#include "myclient.h"

void exect_command(myclient_t *myteams_client, char **command_split)
{
    if (command_split == NULL || command_split[0] == NULL)
        return;
    char *command_tab[15] = {"/help", "/login", "/users", "/logout", "/user",
    "/messages", "/send", "/subscribe",
    "/unsubscribe", "/use", "/create", "/subscribed", "/list", "/info", NULL};
    void (*command_tab_func[15])(myclient_t *, char **) = {\
        &help, &login, &users, &logout, &user, &messages, &sendmsges, &sub,
        &unsub, &use, &create, &subed, &list, &info, NULL};
    if (myteams_client->login == false
        && strcmp("/login", command_split[0]) != 0) {
            client_error_unauthorized();
            return;
    }
    for (int i = 0; i < my_twod_size(command_tab); i++) {
        if (strcmp(command_tab[i], command_split[0]) == 0) {
            command_tab_func[i](myteams_client, command_split);
            return;
        }
    }
    printf("Unknown command.\n");
}
