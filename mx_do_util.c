#include "ush.h"

char **mx_do_util(t_env *env) {
    env->u_flag = malloc(sizeof(char*) * 2);
    
    if (strcmp(env->util, "sh") || strcmp(env->util, "bash")) {
        env->u_name = mx_strjoin("/bin/", env->util);
        env->u_flag[0] = env->util;
        env->u_flag[1] = NULL;
        if (!env->stream_name) {
            env->stream_name = malloc(sizeof(char*) * 2);
            env->stream_name[0] = NULL;
            env->stream_name[1] = NULL;
        }
    }
    return env->stream_name;
}
