#include "ush.h"

char **mx_do_util(t_lst *head, t_env *env) {
    int i = 0;
    int k = 0;
    int j = 0;

    env->u_flag = malloc(sizeof(char *) * 10);
    
    if (env->util[0] != '/') {
        if (env->P)
            env->u_name = mx_strjoin(env->P, env->util);
        else
            env->u_name = mx_strjoin("/bin/", env->util);
        while (strcmp(head->args[i], env->util) < 0) 
            i++;
        if (mx_strcmp(env->util, "bash") == 0) {
            i = 0;
            while (head->args[i])
                i++;
        }
        for (j = i; head->args[j]; j++, k++)
            env->u_flag[k] = mx_strdup(head->args[j]);
        if (!env->stream_name && env->i == 0 && !env->P)
            return head->env;
        else if (env->P) {
            env->stream_name = malloc(sizeof(char*) * 1);
        }
        else if (env->stream_name && env->i == 0)
            env->stream_name = mx_strarr_join(env->stream_name, head->env);
        else if (env->i == 1 && !env->stream_name)
            env->stream_name = malloc(sizeof(char*) * 1);
    }
    else {
        env->u_name = env->util;
        env->u_flag[0] = env->util;
        env->stream_name = malloc(sizeof(char*) * 1);
    }
    return env->stream_name;
}
