/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** help_error
*/

#include "myclient.h"

void print_help(void)
{
    printf("USAGE:\t./myteams_cli ip port\n");
    printf(
        "\tip\tis the server ip address on which the server socket listens\n");
    printf("\tport\tis the port number on which the server socket listens\n");
}

void error_handling(char *str)
{
    perror(str);
    exit(84);
}
