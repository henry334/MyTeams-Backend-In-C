/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** myteams.h
*/

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include <netdb.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include "logging_server.h"
#include "shared.h"

#define USERP "./src/server/database/users/users.txt"
#define MSGP "./src/server/database/messages/messages.txt"
#define TEAMP "./src/server/database/teams/"
#define CHANNELP "./src/server/database/teams/channels/"
#define THREADP "./src/server/database/teams/channels/threads/"

extern struct signal_data {
    bool sigint_received;
} signalss;

typedef struct myteams_serv_s {
    int sock_srv;
    fd_set readfds;
    int max_connect;
    fd_set writefds;
} myteams_serv_t;

typedef struct myteams_client_s {
    int sock_cli;
    unsigned int ip_cli;
    struct sockaddr_in addr_cli;
    char *username;
    char *message;
    bool is_log;
    uuid_t user_uuid;
    char *uuid_str;
    char *uuid_team;
    char *uuid_chanel;
    char *uuid_thread;
} myteams_client_t;

typedef struct my_struct_s {
    myteams_serv_t *server;
    int clientstruct_size;
    myteams_client_t **clientstruct;
} my_struct_t;

static volatile sig_atomic_t run = 1;

void error_handling(char *str);
int check_error_creating(void);
void print_help(void);
int run_teams(char **av);
my_struct_t init_mystruct(void);
myteams_client_t **put_client(my_struct_t *mystruct, myteams_client_t *toadd);
int get_struct(myteams_client_t **clientstruct, int val, char *name);
void free_client(myteams_client_t **tofree);
void add_client(my_struct_t *mystruct, int conffd);
void server_listenning(int sockfd);
char **readdire(char *path);
char *readfile(char *path);
int writefile(char *path, char *start, char *towrite);
int help(my_struct_t *mystruct, int sockfd, char **cmd);
int start_cmd(my_struct_t *mystruct, int client_sock, char *cmd);
int login(my_struct_t *mystruct, int sockfd, char **cmd);
int logout(my_struct_t *mystruct, int sockfd, char **cmd);
myteams_client_t ** remove_client(my_struct_t *mystruct, int client_sock);
void handle_client(myteams_serv_t *server, my_struct_t *mystruct);
int creats(my_struct_t *mystruct, int sockfd, char **cmd);
void sendtxt(int socket, char *text);
int add_client_db(my_struct_t *mystruct, char *uuid_str, char *name);
char **get_client(char *match, int index);
int users(my_struct_t *mystruct, int sockfd, char **cmd);
int user(my_struct_t *mystruct, int sockfd, char **cmd);
int use(my_struct_t *mystruct, int sockfd, char **cmd);
char **get_teams(char *find, char *path, char *start);
void create_threadc(char *thread_uuid, char *user_uuid,int sockfd, char **cmd);
int list(my_struct_t *mystruct, int sockfd, char **cmd);
int info(my_struct_t *mystruct, int sockfd, char **cmd);
void sendmesg(my_struct_t *mystruct, int sockfd, char **cmd);
int send_getmsg(my_struct_t *mystruct, int sockfd, char **cmd);
char **get_msg(char *sender, char *reciver);
int subunsub(my_struct_t *mystruct, int sockfd, char **cmd);
int start_subscribed(my_struct_t *mystruct, int sockfd, char **cmd);
bool is_sub(char *path, char *uuid);
char **get_user(char *find);
int is_log(char *uuid,  my_struct_t *mystruct);
void kill_all_cli(myteams_client_t **clientstruct);
void siginthandler(int signum);
char **get_cmd(char *cmd);
void create_thread(char *c_u, char *user_d, int sockfd, char **cmd);

struct d {
    char *cmd;
    int (*func)(my_struct_t *mystruct, int sockfd, char **cmd);
};
