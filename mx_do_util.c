#include "ush.h"

static char **mx_strarr_dup(char **str) {
    int len = 0;

    while (str[len])
        len++;
    char **target = malloc(sizeof(char *) * len);
    for (int i = 0; i < len; i++)
        target[i] = mx_strdup(str[i]);
    
    target[len] = NULL;
    return target;
}

static char **mx_strarr_join(char **s1, char **s2) {
    char **new_arr = mx_strarr_dup(s1);
    int len_s1 = 0;
    int len_s2 = 0;
    int i = 0;

    if (new_arr) {
        while (new_arr[len_s1])
            len_s1++;
        while (s2[len_s2])
            len_s2++;

        new_arr = realloc(new_arr, sizeof(char *) * (len_s1 + len_s2 + 1));
        i = len_s1;
        for(int j = 0; i < len_s1 + len_s2; j++, i++) {
            new_arr[i] = mx_strdup(s2[j]);
        }
        new_arr[i] = NULL;
    }
    return new_arr;
}

char **mx_do_util(t_lst *head, t_env *env) {
    int i = 0;
    int k = 0;
    int j = 0;

    env->u_flag = malloc(sizeof(char *) * 3);
    env->u_name = mx_strjoin("/bin/", env->util);
    
    while (strcmp(head->args[i], env->util) < 0)
        i++;
    for (j = i + 1; head->args[j]; j++, k++)
        env->u_flag[k] = mx_strdup(head->args[j]);
    if (!env->stream_name && env->i == 0)
        return head->env;
    else if (env->stream_name && env->i == 0)
        env->stream_name = mx_strarr_join(env->stream_name, head->env);
    else if (env->i == 1 && !env->stream_name) {
        mx_printint(1);
    }
    
    return env->stream_name;
}
