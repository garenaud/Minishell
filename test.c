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
