/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 08:20:22 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/06 16:47:40 by grenaud-         ###   ########.fr       */
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
		//printf("je sors de init_pipe_cmd");
	}
}

int	cmd(t_parser *p, t_exe *curr)
{
	signal(SIGINT, handle_sigquit);
	signal(SIGQUIT, handle_sigquit);
	//redirection_tab(curr);
	if (is_builtin(curr->cmd_tab) != -1 && curr->next == NULL)
		bultin_search(p, curr);
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
	
	j = -1;
	int size;
	t_exe	*curr;
	p->piped = checknb_pipe(p->cmd_d);
	size = checknb_arg(p->cmd_d);
	curr = init_exe_list(size);
	p->cmd_exe = curr;
	while (j < p->piped)
	{
		size = checknb_arg(p->cmd_d);
		i = 0;
		while (i < size)
		{
 			if(ft_strcmp(p->cmd_d->key, "3") == 0 || ft_strcmp(p->cmd_d->key, "4") == 0 
				|| ft_strcmp(p->cmd_d->key, "6") == 0 || ft_strcmp(p->cmd_d->key, "7") == 0)
			{
				i = redir(p, p->cmd_d, curr, i);
				//printf("\napres redir la valeur de i est %d", i);
			}
			curr->cmd_tab[i] = ft_strdup(p->cmd_d->value);
			//printf("\n APRES REDIR curr->cmd_tab[%d] = %s et la size %d\n", i, curr->cmd_tab[i], size);
			remove_pos_dico(&p->cmd_d, 0);
			i++;
			if (p->cmd_d == NULL || ft_strncmp(p->cmd_d->value,"|",1) == 0)
				break;
		}
		curr->cmd_tab[i] = NULL;
		
		//printf("apres le nul p->cmd_tab = %s et i = %d", curr->cmd_tab[i - 1], i);
		if (p->cmd_d != NULL)
			remove_pos_dico(&p->cmd_d, 0);	
		if (j != p->piped && p->piped != 0)
		{
			curr->next = init_exe_list(size);
			curr = curr->next;
		}
		j++;
	}
}

