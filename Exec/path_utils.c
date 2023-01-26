/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:26:20 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/26 15:37:08 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*init_path(t_parser *p, char **cmd)
{
	char	*path;

	if (cmd[0] == NULL)
		return (NULL);
	if (access(cmd[0], F_OK | X_OK) != -1 || is_builtin(cmd) == 1)
	{
		path = cmd[0];
		return (path);
	}
	if (access(cmd[0], F_OK | X_OK) == -1 || is_builtin(cmd) != 1)
		return (get_pos_path(p, cmd[0]));
	return (0);
}

char	*get_pos_path(t_parser *p, char *cmd)
{
	int		i;
	char	*path;
	char	*ps;

	i = -1;
	while (++i < (int)size_stack(p->struct_cmd.cmd))
	{
		path = getitem(p->struct_cmd.cmd, i);
		ps = ft_substr(path, ft_strlen(path) - ft_strlen(cmd), ft_strlen(cmd));
		if (ft_strncmp(ps, cmd, ft_strlen(cmd)) == 0)
		{
			free(ps);
			i = -1;
			break ;
		}
		free(ps);
	}
	if (i < 0)
		return (path);
	else
	{
		printf ("Minishell: %s: %s\n", cmd, strerror(22));
		return (NULL);
	}
}
