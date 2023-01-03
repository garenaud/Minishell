/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 08:20:22 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/03 18:54:25 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	piping_main(t_parser *p)
{
	int pfd[2];
	pid_t	pid;
	
	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		init_exe(p);
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
		close(pfd[1]);
		init_pipe_cmd(p);
	}
	close(pfd[1]);
	waitpid(pid, &p->return_val, 0);
	delete(&p->struct_cmd.cmd);
}

void	init_pipe_cmd(t_parser *p)
{
	t_exe	*curr;

	curr = p->cmd_exe;
	if (curr != NULL)
	{
		//init_pipe(curr);
		//printll_exe(curr);
		cmd(p, curr);
	}
}

int	cmd(t_parser *p, t_exe *curr)
{
	signal(SIGINT, handle_sigquit);
	signal(SIGQUIT, handle_sigquit);
	//redirection_tab(curr);
	if (is_builtin(curr->cmd_tab) != -1 && curr->next == NULL)
		bultin_search(curr);
	else
	{	
		if(pipe_exec(p, curr) != 1)
			printf("\n\nben ca a merde kkk");
	}
	return (0);
}


void	init_exe(t_parser *p)
{
	int	i;
	int	j;
	
	j = 0;
	int size;
	t_exe	*curr;
	p->piped = checknb_pipe(p->cmd_d);
	size = checknb_arg(p->cmd_d);
	curr = init_exe_list(size);
	p->cmd_exe = curr;
	while (j <= p->piped)
	{
		size = checknb_arg(p->cmd_d);
		i = 0;
		while (i < size)
		{
			curr->cmd_tab[i] = ft_strdup(p->cmd_d->value);
			remove_pos_dico(&p->cmd_d, 0);
			i++;
		}
		curr->cmd_tab[i] = NULL;
		remove_pos_dico(&p->cmd_d, 0);	
		if (j != p->piped)
		{
			curr->next = init_exe_list(size);
			curr = curr->next;
		}
		j++;
	}
}

