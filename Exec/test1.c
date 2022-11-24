#include "../minishell.h"

#define MAX_ARGC 4 // 3

int main(int argc, char *argv[], char *env[])
 {
    (void) argc;
	(void) argv;
	char *args[][4]= {{"/bin/ls","-allll", NULL},
    {"/usr/bin/grep", "mini", NULL},{"/usr/bin/wc", NULL} };

    int		i;
	int		n;
	int		prev_pipe;
	int		pfds[2];
	n = sizeof(args) / sizeof(*args);
	prev_pipe = STDIN_FILENO;
	i = 0;
	while(i < n - 1)
	{
		pipe(pfds);
		if (fork() == 0)
		{
			if (prev_pipe != STDIN_FILENO)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			dup2(pfds[1], STDOUT_FILENO);
			close(pfds[1]);
			execve(args[i][0], args[i], env);
			perror("execve failed");
			exit(1);
		}
		close(prev_pipe);
		close(pfds[1]);
		prev_pipe = pfds[0];
		i++;
	}
	if (prev_pipe != STDIN_FILENO)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	execve(args[i][0], args[i], env);
	perror("execve failed");
	exit(1);
}
