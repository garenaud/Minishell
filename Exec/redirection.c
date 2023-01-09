/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:53:46 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/09 11:41:58 by grenaud-         ###   ########.fr       */
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
	else if (ft_strcmp(cmd_d->key, "7") == 0)
	{
		append(p, cmd_d, curr);
		i++;
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

int	append(t_parser *p, t_dico *cmd_d, t_exe *curr)
{
	int	fd;

	fd = 0;
	fd = open(cmd_d->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	//printf("je passe par append cmd->next->value = %s\n", cmd_d->next->value);
	if (fd == -1)
	{
		perror("open: ");
		return (-1);
	}
	if (curr->fd_out > 2)
		close(curr->fd_out);
	dup2(fd, 1);
	close(fd);
	curr->fd_out = fd;
	remove_pos_dico(&p->cmd_d, 0);
	//remove_pos_dico(&p->cmd_d, 0);
	//printf("\nAPPEND FINI\n");
	return (0);
}
/* int append(t_parser *p, t_dico *cmd_d, t_exe *curr) {
  int fd;

  fd = open(cmd_d->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
  if (fd == -1) {
    perror("open: ");
    return -1;
  }
  if (curr->fd_out > 2) {
    close(curr->fd_out);
  }
  curr->fd_out = fd;
  return 0;
}
 */