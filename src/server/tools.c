/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** tools
*/

#include "myteams.h"

void sendtxt(int socket, char *text)
{
    write(socket, text, strlen(text));
}