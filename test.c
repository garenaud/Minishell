# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

char    *get_line()
{
    char *line;

    line = NULL;
    if (line)
    {
        free(line);
        line = NULL;
    }
    line = readline("Minishell>");
    if (line)
        add_history(line);
    return (line);
}

void    sig_handler(int signum)
{//https://stackoverflow.com/questions/16828378/readline-get-a-new-prompt-on-sigint
    if (signum == SIGINT)
    {// ordre important !!!
        printf("\n");// va vers une nvlle ligne
        rl_on_new_line();// recree le prompt sur la nvlle ligne
        rl_replace_line("", 0);// efface l'ancien contenu
        rl_redisplay();// et affiche
    }
	if (signum == SIGABRT)
		signal(SIGABRT, SIG_IGN); 
}

int main(void)
{
    char    *line = NULL;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	rl_catch_signals = 0;
	while ((line =readline("mini-->")))
	{
//	signal(SIGINT, sig_handler);
		if (strcmp(line,"quit") == 0)
		{
			free(line);
			break ;
		}
		if (strcmp(line,"") == 0)
		{

        rl_on_new_line();// recree le prompt sur la nvlle ligne
        rl_replace_line("", 0);// efface l'ancien contenu
        rl_redisplay();// et affiche
		}
		if (strcmp(line,"clear") == 0)
			rl_clear_history();
		if (strlen(line) > 0)
		{
			add_history(line);
		}
	//	printf("[%s]\n", line);
		free(line);	
				
	}
}

int main(int argc, char *argv[], char *env[])
 {
    char *args[][4]= {{"/bin/ls","-allll", NULL},
    {"/usr/bin/grep", "mini", NULL},{"/usr/bin/wc", NULL} };
	char	*path1[][3] = {{"/bin/ls", NULL}, {"/usr/bin/grep", NULL}, {"/usr/bin/wc", NULL}};
	char	*arg1[][3] = {{"ls", "-al", NULL}, {"-w", "test", NULL}};
    size_t i, n;
    int prev_pipe, pfds[2];
    n = sizeof(args) / sizeof(*args);
    printf("n = %zu\n", n);
    prev_pipe = STDIN_FILENO;

    for (i = 0; i < n - 1; i++) 
	{
        pipe(pfds);

        if (fork() == 0) 
		{
            // Redirect previous pipe to stdin
            if (prev_pipe != STDIN_FILENO) {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            // Redirect stdout to current pipe
            dup2(pfds[1], STDOUT_FILENO);
            close(pfds[1]);

            // Start command
            execve(*path1[i], arg1[i], env);

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
    if (prev_pipe != STDIN_FILENO) 
	{
        dup2(prev_pipe, STDIN_FILENO);
        close(prev_pipe);
    }
    //execve(args1[0], args1, env);
    // Start last command
     execve(*path1[i], arg1[i], env);
    perror("execve failed");
	if(fork() > 0)
	{
		wait(NULL);
		exit(1);
	}
    exit(1);
} 