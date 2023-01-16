/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:53:46 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/10 13:10:59 by grenaud-         ###   ########.fr       */
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
		input(p, cmd_d, curr);
	else if (ft_strcmp(cmd_d->key, "7") == 0)
	{
		append(p, cmd_d, curr);
		i++;
	}
	else if (ft_strcmp(cmd_d->key, "6") == 0)
		own_heredocs(p, cmd_d, curr);
	return (i);
}

int	output(t_parser *p, t_dico *cmd_d, t_exe *curr, int i)
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
	remove_pos_dico(&p->cmd_d, 0);
	return 0;
}

int	append(t_parser *p, t_dico *cmd_d, t_exe *curr)
{
	int	fd;

	fd = 0;
	fd = open(cmd_d->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
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
	return (0);
}

int	own_heredocs(t_parser *p, t_dico *cmd_d, t_exe *curr)
{
	int		fd[2];
	char	*delimiter;

	delimiter = cmd_d->next->value;
	pipe(fd);
	if (delimiter == NULL)
		return (0);
	own_heredocs_to_long(delimiter, NULL, fd, curr);
	remove_pos_dico(&p->cmd_d, 0);
	return (0);
}

void	own_heredocs_to_long(char *delimiter, char *line, int *fd, t_exe *curr)
{
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(line)) != 0 || line[0] == 0)
		{
			ft_putendl_fd(line, fd[1]);
			free(line);
		}
		else
			break ;
	}
	free(line);
	close (fd[1]);
	if (curr->fd_in > 2)
		close (curr->fd_in);
	curr->fd_in = fd[0];
	return ;
}
