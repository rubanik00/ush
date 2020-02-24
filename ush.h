#ifndef USH_HEADER_H
#define USH_HEADER_H

#include "libmx/inc/libmx.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

// Main loop
void mx_ush_loop(void);
char **mx_ush_split_line(char *line);
char *mx_ush_read_line(void);
int mx_ush_launch(char **args);
int mx_ush_execute(char **args);

#endif
