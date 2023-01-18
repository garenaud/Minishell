/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:00:33 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/17 18:16:23 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_shell(t_parser *p)
{
	t_exe	*curr;

	init_exe(p);
	curr = p->cmd_exe;
	init_pipes(curr);
	if (curr->cmd_tab[0] == NULL)
	{
		delete_exeline(&curr);
		return (0);
	}
	if (p->piped || curr->redir > 0)
	{
		if (pipe_loop(p, curr) != 0)
			return (0);
	}
	else if (inpt_checker(curr->path, curr->cmd_tab, p))
		exit(0);
	return (1);
}

int	pipe_loop(t_parser *p, t_exe *curr)
{
	while (curr != NULL)
	{
		if (curr->fd_in < 0 || curr->fd_out < 0)
		{
			curr = curr->next;
			continue ;
		}
		curr->pid = fork();
		if (curr->pid == 0)
			child_pro(p, curr);
		curr = curr->next;
	}
	waits(p);
	return (0);
}

int	child_pro(t_parser *p, t_exe *curr)
{
	if (curr->fd_in > 2)
		dup2(curr->fd_in, STDIN_FILENO);
	if (curr->fd_out > 2)
		dup2(curr->fd_out, STDOUT_FILENO);
	close_pipes(curr);
	inpt_checker(curr->path, curr->cmd_tab, p);
	exit(0);
}

int	inpt_checker(char *path, char **str, t_parser *p)
{
	if (!(str))
		return (0);
	if (is_builtin(str) == 1)
	{
		if (bultin_search(p->cmd_exe, p) < 0)
			return (1);
	}
	else
		if (is_function(path, str, p))
			return (1);
	return (0);
}

int	is_function(char *path, char **str, t_parser *p)
{
	pid_t	childpid;
	int		i;

	i = 0;
	childpid = fork();
	close_pipes(p->cmd_exe);
	if (childpid == 0)
	{
		if (execve(path, str, p->env) == -1)
			i++;
		exit (127);
	}
	else
		waitpid(childpid, &(p->return_val), 0);
	if (WIFEXITED(p->return_val))
		p->return_val = WEXITSTATUS(p->return_val);
	return (0);
}
