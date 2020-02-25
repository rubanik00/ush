#include "ush.h"

int lsh_num_builtins() {
    char *builtin_str[] = {"cd", "help", "exit"};

    return sizeof(builtin_str) / sizeof(char *);
}

int lsh_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } 
    else {
        if (chdir(args[1]) != 0) {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help() {
    char *builtin_str[] = {"cd", "help", "exit"};
    int i;

    printf("Stephen Brennan's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < lsh_num_builtins(); i++)
        printf("  %s\n", builtin_str[i]);

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int lsh_exit() {
    return 0;
}

/// Нельзя
int (*builtin_func[]) (char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int mx_ush_execute(t_lst *head, t_env *b) {
    char *builtin_str[] = {"cd", "help", "exit"};
    if (head->cmd == NULL)
        return 1;
    if (strcmp(head->cmd, "envp") == 0) {
        return mx_env(head, b);
    }

    for (int i = 0; i < lsh_num_builtins(); i++) {
        if (strcmp(head->cmd, builtin_str[i]) == 0) {
          return (*builtin_func[i])(&head->cmd);
        }
    }
    return mx_ush_launch(&head->cmd);
}
