/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 08:20:22 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/30 15:24:00 by grenaud-         ###   ########.fr       */
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
		//dup2(pfd[1], STDOUT_FILENO);
		close(pfd[0]);
		close(pfd[1]);
		init_pipe_cmd(p);
	}
	//printll_exe(p->cmd_exe);
	//close(pfd[0]);
	close(pfd[1]);
	waitpid(pid, &p->return_val, 0);
	delete(&p->struct_cmd.cmd);
	//printll(p->struct_cmd.cmd);
	//do_waits(p);
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

char	*set_and_get(t_parser *p)
{
	char	*inpt;

	inpt = NULL;
	p->piped = 0;
	//path_update(p);
	if (g_status > 4)
		p->return_val = g_status;
	g_status = WAITING;
	signal(SIGQUIT, SIG_IGN);
	inpt = readline(p->display_path);
	g_status = PARSING;
	if (inpt && ft_isprint(inpt[0]))
		add_history(inpt);
	return (inpt);
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


/* void	init_pipe(t_exe *curr)
{
	int		fd[10][2];
	int		i;

	i = 0;
	curr->fd_in = 0;
	while (i < 10)
	{
		pipe(fd[i]);
		printf("\nfd[%d][0]= %d,fd[%d][1]= %d \n", i,fd[i][0],i, fd[i][1]);
		i++;
	}
	i = 0;
	while (curr->next != NULL)
	{
		//pipe(fd);
		curr->fd_out = fd[i][1];
		printf("\nfd_out = %d\n", fd[i][1]);
		curr->next->fd_in = fd[i][0];
		printf("\nfd_in = %d\n", fd[i][0]);
		curr = curr->next;
		i++;
	}
	curr->fd_out = 1;
} */
void	init_pipe(t_exe *curr)
{
	curr->fd_in = 0;
	while (curr->next != NULL)
	{
		pipe(curr->pfd);
		curr->fd_out = curr->pfd[1];
		curr->next->fd_in = curr->pfd[0];
		curr = curr->next;
	}
	curr->fd_out = 1;
}

void	init_pipes(t_parser *p)
{
	t_exe	*tmp;
	int		fd[2];

	tmp = p->cmd_exe;
	printll_exe(p->cmd_exe);
	printf("\n\n\n print de curr ");
	printll_exe(tmp);
	while (tmp)
	{
		pipe(fd);
		if (!tmp->fd_out)
			tmp->fd_out = fd[1];
		else
			close(fd[1]);
		tmp = tmp->next;
		if (tmp != NULL && !tmp->fd_in)
			tmp->fd_in = fd[0];
		else
			close(fd[0]);
	}
	printf("\n\n\n print de curr apres init pipes ");
	printll_exe(tmp);
	printf("\n\n\n print de cmd_exe apres init pipes ");
	printll_exe(p->cmd_exe);
	//if (!curr->fd_out)
		//curr->fd_out = 1;
}