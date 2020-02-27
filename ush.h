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
    // Exampl comand "cd libmx && ls -l -a"
    char **args;
    char **cmd; // cd
    char **av; // libmx 
    char **env; //env info
    struct s_lst *next; // cmd = ls av = -l -a 
} t_lst;

typedef struct s_env {
    char *key;
    char *val;
    struct s_env *next;
} t_env;

// Main loop
void mx_ush_loop(void);
char **mx_ush_split_line(char *line);
char *mx_ush_read_line(void);
int mx_ush_launch(t_lst *head);
int mx_ush_execute(t_lst *head);


// ENV START
char **mx_env(t_lst *head);

//Node env
t_env *mx_create_node_env(char *envp);
void mx_push_front_env(t_env **ptr, char *envp);
void mx_push_back_env(t_env **ptr, char *envp);

//Copy env
t_env *mx_copy_env(t_env **en, char **envp);
char **mx_env_copy(void);

// ENV END
// Exit
int mx_exit(char **args);

#endif
