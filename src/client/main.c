/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** main
*/

#include "myclient.h"

int main(int ac, char **av)
{
    if (ac != 2 && ac != 3) {
        return 84;
    } else if (ac == 2 && strcmp(av[1], "-help") == 0)
        print_help();
    else
        run_client(av);
}