/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 08:20:22 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/26 15:32:17 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_exe(t_parser *p)
{
	int		i;
	int		redir;
	t_exe	*curr;

	i = -1;
	p->piped = checknb_pipe(p->cmd_d, p);
	p->size = checknb_arg(p->cmd_d, p);
	redir = checknb_redir(p->cmd_d);
	curr = init_exe_list(p->size - redir);
	p->cmd_exe = curr;
	while (i++ < p->piped)
	{
		p->size = checknb_arg(p->cmd_d, p);
		redir = checknb_redir(p->cmd_d);
		fill_exec(p, curr, p->size);
		curr->path = init_path(p, curr->cmd_tab);
		if (p->cmd_d != NULL)
			remove_pos_dico(&p->cmd_d, 0);
		if (i != p->piped && p->piped != 0)
		{
			curr->next = init_exe_list(p->size - redir);
			curr = curr->next;
		}
	}
	return (1);
}

void	fill_exec(t_parser *p, t_exe *curr, int size)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < size)
	{
		if (is_redir(p->cmd_d->key) == 1)
		{
			redir(p, p->cmd_d, curr);
			i += 1;
		}
		if (size_stack_dico(p->cmd_d) != 0 && is_redir(p->cmd_d->key) != 1)
		{
			if (ft_strncmp(p->cmd_d->value, "|", 1) == 0)
				break ;
			curr->cmd_tab[j] = ft_strdup(p->cmd_d->value);
			remove_pos_dico(&p->cmd_d, 0);
			j++;
		}
		else if (p->cmd_d == NULL || ft_strncmp(p->cmd_d->value, "|", 1) == 0)
			break ;
	}
}

void	init_pipes(t_exe *curr)
{
	int		fd[2];

	while (curr->next != NULL)
	{
		pipe(fd);
		if (curr->fd_out == 0)
			curr->fd_out = fd[1];
		else
			close(fd[1]);
		if (curr->next->fd_in == 0)
			curr->next->fd_in = fd[0];
		else
			close(fd[0]);
		curr = curr->next;
	}
	if (curr->fd_out == 0)
		curr->fd_out = 1;
}

void	close_pipes(t_exe *curr)
{
	while (curr)
	{
		if (curr->fd_in > 2)
			close(curr->fd_in);
		if (curr->fd_out > 2)
			close(curr->fd_out);
		curr = curr->next;
	}
}

void	waits(t_parser *p)
{
	t_exe	*curr;

	curr = p->cmd_exe;
	close_pipes(curr);
	while (curr)
	{
		waitpid(curr->pid, &p->return_val, 0);
		curr = curr->next;
	}
}
