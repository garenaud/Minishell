/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:42:43 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/05 11:55:47 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_exec(t_parser *p, t_exe *curr)
{
	int	prev_pipe;
	int	i;
	int	size;
	char	*path;

	i = 0;
	size = size_stack(p->struct_cmd.cmd);
	prev_pipe = STDIN_FILENO;
	while(i < size - 1)
	{
		pipe(curr->pfd);
		curr->pid = fork();
		path = get_pos_path(p, curr->cmd_tab[0]);
		if(curr->pid == 0)
		{
 			if (curr->fd_in > 0)
			{
				dup2(prev_pipe, curr->fd_in);
				close(prev_pipe);	
			}	
			else if (prev_pipe != STDIN_FILENO)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if (curr->fd_out > 0)
				dup2(curr->pfd[1], curr->fd_out);
			else
				dup2(curr->pfd[1], STDOUT_FILENO);
			close(curr->pfd[1]);
			//close(curr->pfd[0]);
			execve(path, curr->cmd_tab, p->env);
			perror("execve failed pipe");
			close(prev_pipe);
			exit(1);
		}
		close(prev_pipe);
		close(curr->pfd[1]);
		prev_pipe = curr->pfd[0];
		curr = curr->next;
		i++;
	}
	if (prev_pipe != STDIN_FILENO)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	path = get_pos_path(p, curr->cmd_tab[0]);
	execve(path, curr->cmd_tab, p->env);
		perror("execve failed last command");
	close(prev_pipe);
	close(curr->pfd[1]);
	do_waits(p);
	return(1);
}

void	do_waits(t_parser *p)
{
	while (waitpid(-1, &p->return_val, WUNTRACED) < 0)
		continue;
	if (errno != ECHILD)
	{
		//ERROR
		printf("\n la merde!!!! c'est dowait qui le dit\n");
	}
	if (WIFEXITED(p->return_val))
	{
		g_status = WEXITSTATUS(p->return_val);
	}
}

void	free_cmds(t_parser	*p)
{
	t_exe	*curr;
	t_exe	*next;

	curr = p->cmd_exe;
	while (curr)
	{
		next = curr->next;
		if (curr->cmd_tab)
		{
			free_tab(curr->cmd_tab);
			free(curr->cmd_tab);
		}
		free(curr);
		curr = next;
	}
}

int	free_all(t_parser *p)
{
	if (p->cmd_exe->cmd_tab != NULL)
	{
		free_tab(p->cmd_exe->cmd_tab);
		free(p->cmd_exe->cmd_tab);
	}
	return (0);
}
