/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:53:46 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/18 10:08:03 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	output(t_parser *p, t_dico *cmd_d, t_exe *curr)
{
	int	fd;

	fd = 0;
	curr->redir = 1;
	if (cmd_d == NULL || curr == NULL)
		return (-1);
	fd = open(cmd_d->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd_d->next->value);
		return (1);
	}
	if (curr->fd_out > 2)
		close(curr->fd_out);
	curr->fd_out = fd;
	remove_pos_dico(&p->cmd_d, 0);
	remove_pos_dico(&p->cmd_d, 0);
	return (0);
}

int	input(t_parser *p, t_dico *cmd_d, t_exe *curr)
{
	int	fd;

	fd = 0;
	curr->redir = 2;
	if (cmd_d == NULL || curr == NULL)
		return (-1);
	fd = open(cmd_d->next->value, O_RDONLY);
	if (fd == -1)
	{
		printf ("Minishell: %s: %s\n", cmd_d->next->value, strerror(2));
		remove_pos_dico(&p->cmd_d, 0);
		remove_pos_dico(&p->cmd_d, 0);
		return (-1);
	}
	if (curr->fd_in > 2)
		close(curr->fd_in);
	curr->fd_in = fd;
	remove_pos_dico(&p->cmd_d, 0);
	remove_pos_dico(&p->cmd_d, 0);
	return (0);
}

int	append(t_parser *p, t_dico *cmd_d, t_exe *curr)
{
	int	fd;

	fd = 0;
	curr->redir = 3;
	fd = open(cmd_d->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open : ");
		return (-1);
	}
	if (curr->fd_out > 2)
		close(curr->fd_out);
	curr->fd_out = fd;
	remove_pos_dico(&p->cmd_d, 0);
	remove_pos_dico(&p->cmd_d, 0);
	return (0);
}

int	own_heredocs(t_parser *p, t_dico *cmd_d, t_exe *curr)
{
	int		fd[2];
	char	*delimiter;

	curr->redir = 4;
	delimiter = cmd_d->next->value;
	pipe(fd);
	if (delimiter == NULL)
		return (0);
	own_heredocs_to_long(delimiter, NULL, fd, curr);
	remove_pos_dico(&p->cmd_d, 0);
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
	if (curr->fd_in > 2)
		close (curr->fd_in);
	close(fd[1]);
	curr->fd_in = fd[0];
}
