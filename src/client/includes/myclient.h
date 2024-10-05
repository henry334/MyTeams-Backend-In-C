/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** myteams.h
*/

#pragma once

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <signal.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "shared.h"
#include "logging_client.h"

typedef struct line_s {
    char value;
    struct line_s *next;
} line_t;

typedef struct myclient_s {
    int fd;
    char *ip;
    int port;
    bool exit;
    bool login;
    fd_set readfds;
    char *user_name;
    char *user_uuid;
} myclient_t;

void print_help(void);
char *get_command(int fd, myclient_t *myteams_client);
void run_client(char **av);
void error_handling(char *str);
void quit(myclient_t *myteams_client, char **command);
void help(myclient_t *myteams_client, char **command);
void login(myclient_t *myteams_client, char **command);
void users(myclient_t *myteams_client, char **command);
void get_message(myclient_t *myteams_client,
    char *command, char **command_split);
char *clean_command(char *command);
void exect_command(myclient_t *myteams_client, char **command_split);
void logout(myclient_t *myteams_client, char **command);
void user(myclient_t *myteams_client, char **command);
void sendmsges(myclient_t *myteams_client, char **command);
void messages(myclient_t *myteams_client, char **command);
char **get_cmd(char *cmd);
bool wait_write(myclient_t *myteams_client);
bool wait_read(int fd);
void sub(myclient_t *myteams_client, char **command);
void unsub(myclient_t *myteams_client, char **command);
void use(myclient_t *myteams_client, char **command);
void create(myclient_t *myteams_client, char **command);
char *concat_msg(char **command);
char **pass(char *cmd);
int set_zero(int sockfd, myclient_t *myteams_client);
void subed(myclient_t *myteams_client, char **command);
void list(myclient_t *myteams_client, char **command);
char **rm_gui(char **command);
void print_erro(char *error, char *uuid);
void info(myclient_t *myteams_client, char **command);