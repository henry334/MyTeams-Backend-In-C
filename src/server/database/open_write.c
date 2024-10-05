/*
** EPITECH PROJECT, 2023
** B-NWP-400-BAR-4-1-myteams-thomas.fiancette
** File description:
** open_write
*/

#include "myteams.h"

int writefile(char *path, char *start, char *towrite)
{
    int fl = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    char *buffer = malloc(sizeof(char) *
        ((strlen(start) + strlen(towrite)) + 1));
    sprintf(buffer, "%s%s", start, towrite);
    write(fl, buffer, strlen(buffer));
    free(buffer);
    close(fl);
    return 0;
}

char *readfile(char *path)
{
    int rt;
    int file;
    struct stat size_buf;
    stat(path, &size_buf);
    file = open(path, O_RDONLY);
    if (file == -1)
        return NULL;
    char *buffer = malloc(size_buf.st_size + 3);
    rt = read(file, buffer, size_buf.st_size);
    if (rt == -1) {
        free(buffer);
        return NULL;
    }
    buffer[rt] = '\0';
    return buffer;
}

int getsize(DIR *temp)
{
    struct dirent *entry;
    int val = 0;
    while ((entry = readdir(temp)) != NULL) {
        if (entry->d_name[0] != '.')
            val++;
    }
    closedir(temp);
    return val;
}

char **readdire(char *path)
{
    struct dirent *entry;
    DIR *dir = opendir(path);
    DIR *temp = opendir(path);
    if (dir == NULL)
        return NULL;
    int val = getsize(temp);
    char **buff = malloc((val + 2) * sizeof(*buff));
    val = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            buff[val] = add(entry->d_name, 0, strlen(entry->d_name));
            val++;
        }
    }
    buff[val] = NULL;
    closedir(dir);
    return buff;
}