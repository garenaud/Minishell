/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:44:55 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/30 17:10:04 by grenaud-         ###   ########.fr       */
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

char	*get_cmd_path(t_parser *p, t_exe *curr)
{
	int		pos_path;
	char	*path;
	
	pos_path = getpos(p->struct_cmd.cmd, curr->cmd_tab[0]);
	printf(GREEN"\nle pos_path: %d et la cmd: %s\n", pos_path, curr->cmd_tab[0]);
	printll(p->struct_cmd.cmd);
	path = getitem(p->struct_cmd.cmd, pos_path);
	printf(" le chemin: %s", path);
	printf(ENDC);
	return(path);
}