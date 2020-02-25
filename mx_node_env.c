#include "ush.h"

t_env *mx_create_node_env(char *envp) {
    t_env *node = malloc(sizeof(t_env));
    int index = mx_get_char_index(envp, '=');

    node->key = strndup(envp, index);
    node->val = strndup(envp + index + 1, strlen(envp) - index);
    node->next = NULL;
    return node;
}

void mx_push_front_env(t_env **ptr, char *envp) {
    t_env *node = NULL;

    if(!ptr)
        return;
    node = mx_create_node_env(envp);
    node->next = *ptr;
    *ptr = node;
}

void mx_push_back_env(t_env **ptr, char *envp) {
    t_env *node = NULL;
    t_env *tmp = NULL;

    if (!ptr)
        return;
    node = mx_create_node_env(envp);
    tmp = *ptr;
    if(!*ptr) {
        *ptr = node;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}
