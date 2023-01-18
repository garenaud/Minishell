/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:44:55 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/18 13:57:18 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checknb_arg(t_dico *top)
{
	int	i;

	i = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->value, "|", 1) == 0)
			return (i);
		top = top->next;
		i++;
	}
	return (i);
}

int	checknb_pipe(t_dico *top)
{
	int	i;

	i = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->value, "|", 1) == 0)
			i++;
		top = top->next;
	}
	return (i);
}

int	if_path_not_exist(t_exe *curr, char **path_tab, char **env)
{
	int	i;

	(void)path_tab;
	i = 0;
	if (execve(*curr->cmd_tab, &curr->cmd_tab[i], env) == -1)
			i++;
	if (i == 0)
	{
		return (-1);
	}
	return (0);
}

char	*get_pos_path(t_parser *p, char *cmd)
{
	int		i;
	char	*path;
	char	*ps; //path_search

	i = -1;
	printf("\ncmd = %s et sizestack = %d\n\n", cmd, (int)size_stack(p->struct_cmd.cmd));
	if (cmd == NULL)
		return (0);
	while (++i < (int)size_stack(p->struct_cmd.cmd))
	{
		path = getitem(p->struct_cmd.cmd, i);
		printf("cmd = %s, path = %s\n\n", cmd, path);
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
