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

static void print_stream_env(t_env *env) {
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

static int cheack_u (t_env *env) {
    for (int i = 0; env->u[i]; i++) {
        if (env->u[i] == '=') {
            mx_printerr("env: unsetenv ");
            mx_printstr(env->u);
            mx_printerr(": Invalid argument\n");
            exit (1);
            return 0;
        }
    }
    return 1;
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
        if (!env->stream_name)
            return NULL;
        else {
            print_stream_env(env);
            return NULL;
        }
    }
    else if (env->u) {
        if (cheack_u(env) == 0)
            return NULL;
        for (int i = 0; head->env[i]; i++) {
            if (strncmp(head->env[i], env->u, strlen(env->u)) == 0)
                i++;
            else {
                mx_printstr(head->env[i]);
                mx_printstr("\n");
            }
        }
        if (env->stream_name)
            print_stream_env(env);
    }
    else {
        mx_print_strarr(head->env, "\n");
        if (env->stream_name)
           print_stream_env(env); 
        return NULL;
    }
    return NULL;
}
