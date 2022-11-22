#include "../minishell.h"

#define MAX_ARGC 4 // 3

int main(int argc, char *argv[], char *env[])
 {
    char *args[][4]= {{"/bin/ls","-allll", NULL},
    {"/usr/bin/grep", "mini", NULL},{"/usr/bin/wc", NULL} };

    size_t i, n;
    int prev_pipe, pfds[2];
    n = sizeof(args) / sizeof(*args);
    printf("n = %zu\n", n);
    prev_pipe = STDIN_FILENO;

    for (i = 0; i < n - 1; i++) {
        pipe(pfds);

        if (fork() == 0) {
            // Redirect previous pipe to stdin
            if (prev_pipe != STDIN_FILENO) {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            // Redirect stdout to current pipe
            dup2(pfds[1], STDOUT_FILENO);
            close(pfds[1]);

            // Start command
            execve(args[i][0], args[i], env);

            perror("execve failed");
            exit(1);
        }

        // Close read end of previous pipe (not needed in the parent)
        close(prev_pipe);

        // Close write end of current pipe (not needed in the parent)
        close(pfds[1]);

        // Save read end of current pipe to use in next iteration
        prev_pipe = pfds[0];
    }

    // Get stdin from last pipe
    if (prev_pipe != STDIN_FILENO) {
        dup2(prev_pipe, STDIN_FILENO);
        close(prev_pipe);
    }
    //execve(args1[0], args1, env);
    // Start last command
     execve(args[i][0], args[i], env);

    perror("execve failed");
    exit(1);
}
