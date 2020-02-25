#include "ush.h"

int main(int argc, char **argv, char **envp) {
    t_env *b = mx_copy_env(&b, envp);
    
    argc = 0;
    argv = NULL;
    mx_ush_loop(b);
    return 0;
}
