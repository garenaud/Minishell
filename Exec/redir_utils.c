/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:28:41 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/26 15:40:25 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir(t_parser *p, t_dico *cmd_d, t_exe *curr)
{
	if (redir_error(p, cmd_d, curr) == 1)
	{
		curr->error = 1;
		return (0);
	}
	if (cmd_d->next == NULL)
	{
		printf ("Minishell: syntax error near unexpected token `newline'\n");
		p->return_val = 258;
		return (-32);
	}
	else if (ft_strcmp(cmd_d->key, "3") == 0)
		output(p, cmd_d, curr);
	else if (ft_strcmp(cmd_d->key, "4") == 0)
		input(p, cmd_d, curr);
	else if (ft_strcmp(cmd_d->key, "7") == 0)
		append(p, cmd_d, curr);
	else if (ft_strcmp(cmd_d->key, "6") == 0)
		own_heredocs(p, cmd_d, curr);
	return (0);
}

int	redir_error(t_parser *p, t_dico *cmd_d, t_exe *curr)
{
	(void) curr;
	if (cmd_d->next != NULL && cmd_d->next->next != NULL
		&& is_redir(cmd_d->next->key))
	{
		if (ft_strcmp(cmd_d->key, "4") == 0)
		{
			if (ft_strcmp(cmd_d->next->key, "3") == 0)
				remove_pos_dico(&cmd_d, 0);
			else
			{
				printf (SYNERR, cmd_d->next->value);
				p->return_val = 258;
				return (1);
			}
		}
		else
		{
			printf (SYNERR, cmd_d->next->value);
			p->return_val = 258;
			return (1);
		}
	}
	return (0);
}

int	is_redir(char *key)
{
	if (!ft_strcmp(key, "3") || !ft_strcmp(key, "4")
		|| !ft_strcmp(key, "6") || !ft_strcmp(key, "7"))
		return (1);
	else
		return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
