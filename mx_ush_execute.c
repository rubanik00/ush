#include "ush.h"

int mx_ush_execute(t_lst *head) {

    if (head->cmd == NULL)
        return 1;
    if (strcmp(head->cmd, "envp") == 0) {
        return mx_env(head, head->env);
    }
    
    return mx_ush_launch(&head->cmd, head->env);
}
