#include "ush.h"

static void check_valid_av(char *av) {
    int i = 0;
    int index = mx_get_char_index(av, '=');    
    char *frst_part = strndup(av, index);
    char *sec_part = strndup(av + index + 1, strlen(av) - index);

    if (frst_part[0] == '!') {
        mx_printerr(av);
        mx_printerr(": event not found\n");
    }
    while (sec_part[i]) {
        if (sec_part[i] == '!'
            && (sec_part[i + 1] != '=' && sec_part[i + 1] != '\0')) {
            mx_printerr(av);
            mx_printerr(": event not found\n");
        }
        i++;
    }
}

static void print_env(t_env *env) {
    for (int i = 0; env->stream_name[i]; i++) { 
        check_valid_av(env->stream_name[i]);
        mx_printstr(env->stream_name[i]);
        mx_printchar('\n');
    }
}

static void print_error(t_env *env) {
        mx_printerr("env: illegal option -- ");
        mx_printchar(env->error);
        mx_printchar('\n');
        mx_printerr("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
        mx_printerr("\t   [name=value ...] [utility [argument ...]]\n");
}

char **mx_env(t_lst *head, t_env *env) {
    if (env->error) {
        print_error(env);
        return NULL;
    }
    if (env->util)
        return mx_do_util(head, env);
    if (!head->args[1]) {
        mx_print_strarr(head->env, "\n");
        return NULL;
    }
    else if (env->i == 1) {
        if (!env->stream_name) {
            return NULL;
        }
        else {
            print_env(env);
            return NULL;
        }
    }
    else {
        mx_print_strarr(head->env, "\n");
        if (env->stream_name) {
           print_env(env); 
        }
        return NULL;
    }
    return NULL;
}
