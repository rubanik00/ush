#include "ush.h"

t_env *mx_copy_env(t_env **en, char **envp) {
    for (int i = 0; envp[i]; i++)
        mx_push_back_env(en, envp[i]);
    return *en;
}
