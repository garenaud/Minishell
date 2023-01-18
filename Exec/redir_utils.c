/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:28:41 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/18 14:14:30 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir(t_parser *p, t_dico *cmd_d, t_exe *curr, int i)
{
	printf("je passe par redir, i = %d, cmd_d = %s\n", i, p->cmd_d->value);
	if (ft_strcmp(cmd_d->key, "3") == 0)
	{
		output(p, cmd_d, curr);
		i += 1;
	}
	else if (ft_strcmp(cmd_d->key, "4") == 0)
	{
		input(p, cmd_d, curr);
		i += 1;
	}	
	else if (ft_strcmp(cmd_d->key, "7") == 0)
	{
		append(p, cmd_d, curr);
		i += 2;
	}
	else if (ft_strcmp(cmd_d->key, "6") == 0)
	{
		own_heredocs(p, cmd_d, curr);
		i += 1;
	}
	return (i);
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

char	*ft_realloc(char *org, int n_size)
{
	char	*new;

	new = malloc(n_size);
	if (!new)
		return (NULL);
	ft_strcpy(new, org);
	if (org)
		free (org);
	return (new);
}
