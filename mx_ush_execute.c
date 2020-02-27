#include "ush.h"

static int mx_find_builtin(t_lst *head) {

    if (strcmp(head->args[0], "env") == 0)
        return mx_ush_launch(head);
    if (strcmp(head->args[0], "exit") == 0)
        return mx_exit(head->args);
    return 0;
}

int mx_ush_execute(t_lst *head) {
    char **env = mx_env_copy();
    
    head->env = env;
    if (head->args[0] == NULL)
        return 1;

    return mx_find_builtin(head) ? 1 : mx_ush_launch(head);
}
