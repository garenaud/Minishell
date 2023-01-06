/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:53:46 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/06 10:40:37 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir(t_parser *p, t_dico *cmd_d, t_exe *curr, int i)
{
	if (ft_strcmp(cmd_d->key, "3") == 0)
	{
		output(p, cmd_d, curr, i);
		i += 2;
	}
	else if (ft_strcmp(cmd_d->key, "4") == 0)
	{
		input(p, cmd_d, curr);
		//printf("finis input \n");
		//i++;
	}
	return (i);	
}

int output(t_parser *p, t_dico *cmd_d, t_exe *curr, int i) 
{
	if (cmd_d == NULL || curr == NULL) 
		return -1;
	int fd = open(cmd_d->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1) 
	{
		perror("open: ");
		return -1;
	}
	if (curr->fd_out > 2)
		close(curr->fd_out);
	dup2(fd, 1);
	close(fd);
	curr->fd_out = fd;
	//printf("cmd_d depuis input = %s et la valeur de i = %d\n", cmd_d->value, i);
	remove_pos_dico(&p->cmd_d, i);
	remove_pos_dico(&p->cmd_d, i + 1);
	return 0;
}

int input(t_parser *p, t_dico *cmd_d, t_exe *curr) 
{
	if (cmd_d == NULL || curr == NULL)
		return -1;
	int fd = open(cmd_d->next->value, O_RDONLY, 0644);
	if (fd == -1) 
	{
		perror("open: ");
		return(-1);
	}
	if (curr->fd_in > 2)
    	close(curr->fd_in);
	dup2(fd, 0);
	close(fd);
	curr->fd_in = fd;
	//printf("cmd_d depuis input = %s et la valeur de i = %d\n", cmd_d->value, i);
	remove_pos_dico(&p->cmd_d, 0);
	//i++;
	return 0;
}


/* int	output(t_dico *cmd_d, t_exe *curr)
{
	int	fd;

	//printf("\ncurr->cmd_tab[%d] = %s", i, curr->cmd_tab[i + 1]);
	fd = open(cmd_d->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open: ");
		return (-1);
	}
	if (curr->fd_out > 2)
		close(curr->fd_out);
	curr->fd_out = fd;
	printf("\nle fd_out est = %d\n", curr->fd_out);
	return (0);
} */

/* int	input(t_dico *cmd_d, t_exe *curr)
{
	int	fd;

	fd = open(cmd_d->next->value, O_RDONLY, 0644);
	if (fd == -1)
	{
		perror("open: ");
		return (-1);
	}
	if (curr->fd_in > 2)
		close(curr->fd_in);
	curr->fd_in = fd;
	printf("\nle fd_in est = %d\n", curr->fd_in);
	return (0);
} */