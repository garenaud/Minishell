/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:39:37 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/25 14:35:30 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

/* #define MAX_ARGC 4 // 3

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
} */

char	*getitem_c(t_list *top, size_t pos)
{
	if (pos >= size_stack(top))
		return (NULL);
	else
	{
		while (pos > 0)
		{
			top = top->next;
			pos--;
		}
		return (top->data);
	}
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		str++;
		count++;
	}
	return (count);
}

char	*ft_strdup(char *src)
{// la version normal ok, remise a normal
	char	*dst;

	dst = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));// leak
	if (dst == NULL)
		return (NULL);
	ft_strcpy(dst, src);
/* 	if (free_it)
		free(src);  */
//	free((char *)src);
//	printf("<%p> strdup\n", dst);
	return (dst);
}

void	push(t_list **top, char	 *item)
{
	t_list	*tmp;
	
//	printf("<%p>\n", *top);
	tmp = malloc(sizeof(t_list));
	if (!tmp)
		return;
//	printf("<%p> push\n", tmp);
	tmp->data = ft_strdup(item);
	tmp->next = *top;
	*top = tmp; //?
}

void	printll(t_list *lst)
{
	printf("start");
	while (lst)
	{
		printf("-->[%s]\n", (lst->data));
		lst = lst->next;
	}
	printf("-->[end]\n");
}

size_t	size_stack(t_list *top)
{
	size_t	size;

	size = 0;
	while (top != NULL)
	{
		size++;
		top = (top)->next;
	}
	return (size);
}

void	pipe_cmd(char *cmd[], char *arg[], char *env[])
{
	int	status;
	int	nb_pipes;
	int	i;
	int	j;
	char	*tmp;
	char	*tmp_arg;
	pid_t	pid;
	int	pipefds[2*nb_pipes];

	i = 0;
	nb_pipes = sizeof(&cmd);

	while (i++ < nb_pipes)
	{
		if (pipe(pipefds + i*2) < 0)
		{
			perror("couldn't pipe");
			exit(EXIT_FAILURE);
		}
	}
	j = 0;
	while(cmd)
	{
		pid = fork();
		if(pid == 0)
		{
			if(cmd[i + 1] != NULL) //path_cmd->next
				if(dup2(pipefds[j + 1], 1) < 0)
				{
					perror("dup 2 failed");
					exit(EXIT_FAILURE);
				}
			if (j != 0)
				if (dup2(pipefds[j-2], 0) < 0)
				{
					perror("dup 2 failed");
					exit(EXIT_FAILURE);
				}
			i = 0;
			while (i++ < 2 * nb_pipes)
				close(pipefds[i]);
		}
		if (execve(&cmd[i][0], &arg[i], env) < 0)
		{
			perror(tmp_arg);
			exit(EXIT_FAILURE);
		}
		tmp = cmd[i + 1];
		printf(RED"cmd[%i] = %s"ENDC, i, tmp);
		j+=2;
	}
	i = 0;
	while(i++ < 2 * nb_pipes)
		close(pipefds[i]);
	i = 0;
	while (i++ < nb_pipes + 1)
		wait(&status);
}

int main(int argc, char *argv[], char *env[])
{
    (void) argc;
	(void) argv;
	char *cmd[4]= {"/bin/ls", "/usr/bin/grep", "/usr/bin/wc", NULL};
	char *arg[4]= {"-la", "mini", " ", NULL};
	pipe_cmd(cmd, arg, env);
	return(0);
}

/* void runPipedCommands(cmdLine* command, char* userInput) 
{
    int numPipes = countPipes(userInput);


    int status;
    int i = 0;
    pid_t pid;

    int pipefds[2*numPipes];

    for(i = 0; i < (numPipes); i++)
	{
        if(pipe(pipefds + i*2) < 0) 
		{
            perror("couldn't pipe");
            exit(EXIT_FAILURE);
        }
    }


    int j = 0;
    while(command) 
	{
        pid = fork();
        if(pid == 0) 
		{

            //if not last command
            if(command->next)
			{
                if(dup2(pipefds[j + 1], 1) < 0)
				{
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            //if not first command&& j!= 2*numPipes
            if(j != 0 )
			{
                if(dup2(pipefds[j-2], 0) < 0){
                    perror(" dup2");///j-2 0 j+1 1
                    exit(EXIT_FAILURE);

                }
            }


            for(i = 0; i < 2*numPipes; i++){
                    close(pipefds[i]);
            }

            if( execvp(*command->arguments, command->arguments) < 0 ){
                    perror(*command->arguments);
                    exit(EXIT_FAILURE);
            }
        } else if(pid < 0)
		{
            perror("error");
            exit(EXIT_FAILURE);
        }

        command = command->next;
        j+=2;
    }
    Parent closes the pipes and wait for children

    for(i = 0; i < 2 * numPipes; i++){
        close(pipefds[i]);
    }

    for(i = 0; i < numPipes + 1; i++)
        wait(&status);
}
 */