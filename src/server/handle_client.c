/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** handle_client
*/

#include "myteams.h"

my_struct_t init_mystruct(void)
{
    my_struct_t mystruct;
    mystruct.clientstruct_size = 0;
    mystruct.clientstruct = (myteams_client_t**)malloc((1)
            * sizeof(myteams_client_t*));
    mystruct.clientstruct[0] = NULL;
    return mystruct;
}

myteams_client_t **put_client(my_struct_t *mystruct, myteams_client_t *toadd)
{
    int i;
    myteams_client_t **temp =
    (myteams_client_t**)malloc((mystruct->clientstruct_size + 2)
        * sizeof(myteams_client_t*));
    for (i = 0; mystruct->clientstruct[i] != NULL; i++) {
        temp[i] = mystruct->clientstruct[i];
    }
    temp[i] = toadd;
    temp[i + 1] = NULL;
    if (mystruct->clientstruct_size == 0)
        free_client(mystruct->clientstruct);
    mystruct->clientstruct_size++;
    return temp;
}

int get_struct(myteams_client_t **clientstruct, int val, char *name)
{
    for (int i = 0; clientstruct[i] != NULL; i++) {
        if (clientstruct[i]->sock_cli == val)
            return i;
        if (val == -1 && (strcmp(clientstruct[i]->username, name) == 0
            || strcmp(clientstruct[i]->uuid_str, name) == 0 ))
                return i;
    }
    return -1;
}

myteams_client_t **remove_client(my_struct_t *mystruct, int client_sock)
{
    int index = get_struct(mystruct->clientstruct, client_sock, "");
    myteams_client_t **temp =
    (myteams_client_t**)malloc((mystruct->clientstruct_size)
        * sizeof(myteams_client_t*));
    int p = 0;
    for (int i = 0; mystruct->clientstruct[i] != NULL; i++) {
        if (i != index) {
            temp[p] = mystruct->clientstruct[i];
            p++;
        }
    }
    temp[p] = NULL;
    mystruct->clientstruct_size--;
    return temp;
}

void add_client(my_struct_t *mystruct, int conffd)
{
    myteams_client_t *temp =
        (myteams_client_t*)malloc(sizeof(myteams_client_t));
    temp->sock_cli = conffd;
    temp->is_log = false;
    temp->username = strdup("Anonymous");
    uuid_generate(temp->user_uuid);
    char uuid_str[37];
    uuid_unparse(temp->user_uuid, uuid_str);
    temp->uuid_str = strdup(uuid_str);
    temp->uuid_chanel = NULL;
    temp->uuid_team = NULL;
    temp->uuid_thread = NULL;
    mystruct->clientstruct = put_client(mystruct, temp);
}