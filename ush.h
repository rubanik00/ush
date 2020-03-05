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

typedef struct s_lst {
    char **args;
    char **env;
    struct s_lst *next;
} t_lst;

typedef struct s_env {
    bool i;
    char *P;
    char *u;
    char **stream_name;
    char *util;
    char *u_name;
    char **u_flag;
    char error;
    char **key;
    char **val;

    struct s_env *next;
} t_env;

// Main loop
void mx_ush_loop(void);
char **mx_ush_split_line(char *line);
char *mx_ush_read_line(void);
int mx_ush_execute(t_lst *head);
int mx_ush_launch(t_lst *head);

// ENV START
t_env *mx_create_env(char *env);
char **mx_env_copy(void);
t_env *mx_parse_env(char **args);
char **mx_env(t_lst *head, t_env *env);
char **mx_do_util(t_lst *head, t_env *env);
// ENV END
char **mx_strarr_dup(char **str);
char **mx_strarr_join(char **s1, char **s2);
// Exit
int mx_exit(char **args);

#endif
