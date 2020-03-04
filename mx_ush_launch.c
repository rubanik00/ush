#include "ush.h"

static int choose_exec(t_lst *head) {
    char **new_env;
    int status = 0;
    t_env *env = malloc(sizeof(t_env));
    
    if (strcmp(head->args[0], "env") == 0) {
        env = mx_parse_env(head->args);
        new_env = mx_env(head, env);

        if (new_env == NULL)
            return 1;
        else {
            status = execve(env->u_name, env->u_flag, new_env);
            if (env->i == 1 && !env->stream_name)
                mx_strdel(env->stream_name);
        }
    }
    else {
        if ((status = execvp(head->args[0], head->args)) == -1)
            mx_printerr("ERROR2\n");
        exit(0);
    }
    free(env);
    return status;
}

int mx_ush_launch(t_lst *head) {
    pid_t pid = fork();
    int status = 0;

    if (pid == 0) {
        if ((status = choose_exec(head)) < 0) {
            mx_printstr("ERROR1\n");
            return 0;
        }
        exit(status);
    }
    if (pid < 0) {
        mx_printerr("ush: error starting a new proccess: ");
        mx_printerr(head->args[0]);
    }
    else
        status = waitpid(pid, &status, WUNTRACED);
    return status;
}
