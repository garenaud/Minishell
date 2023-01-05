/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:44:55 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/04 11:14:21 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		checknb_arg(t_dico *top)
{
	int	i;
	i = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->value,"|",1) == 0)
			return (i);
		top = top->next;
		i++;
	}
	return (i);	
}

int		checknb_pipe(t_dico *top)
{
	int i;
	i = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->value,"|",1) == 0)
			i++;
		top = top->next;
	}
	return (i);
}

int	ft_pipetok(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
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
	char	*path_search;
	
	i = 0;
	while (i < (int)size_stack(p->struct_cmd.cmd))
	{
		path = getitem(p->struct_cmd.cmd, i);
		path_search = ft_substr(path, ft_strlen(path) - ft_strlen(cmd), ft_strlen(cmd));
		if (ft_strcmp(path_search, cmd) == 0)
		{
			free(path_search);
			break;
		}
		i++;
		free(path_search);
	}
	return(path);
}
