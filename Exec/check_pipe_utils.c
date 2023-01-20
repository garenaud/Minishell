/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:44:55 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/20 16:37:23 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checknb_arg_calloc(t_dico *top)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->value, "|", 1) == 0)
			return (i);
		if (is_redir(top->key) == 1)
		{
			j++;
			//printf("redir\n");
			if (top->next != NULL || ft_strncmp(top->value, "|", 1) != 0)
				j++;
				//printf("redir2\n");}
		}
		top = top->next;
		i++;
	}
	if (i < j)
		i = 0;
	else
		i = i - j;
	printf(RED"j = %d, i = %d\n"ENDC, j, i);
	return (i);
}

int	checknb_redir(t_dico *top)
{
	int	i;

	i = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->value, "|", 1) == 0)
			return (i);
		if (is_redir(top->key) == 1)
		{
			i += 2;
			top = top->next;
		}
		top = top->next;
	}
	return (i);
}

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

int	ft_pipetok(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

/* int	if_path_not_exist(t_exe *curr, char **path_tab, char **env)
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
} */

char	*init_path(t_parser *p, char **cmd)
{
	char	*path;

	if (cmd[0] == NULL)
		return (NULL);
	//printf("cmd[0][0] = %c, cmd[1][0] = %c\n", p->cmd_d->value[0], p->cmd_d->next->value[0]);
	if (access(cmd[0], F_OK | X_OK) != -1 || is_builtin(cmd) == 1)
	{
		path = cmd[0];
		return (path);
	}
	if (access(cmd[0], F_OK | X_OK) == -1 || is_builtin(cmd) != 1)
		return (get_pos_path(p, cmd[0]));
/* 	if (ft_pipetok(p->cmd_d->value[0]) || ft_pipetok(p->cmd_d->next->value[0]))
	{
		printf("\nredir apres\n");
		return (0);
	} */
	return (0);
}

char	*get_pos_path(t_parser *p, char *cmd)
{
	int		i;
	char	*path;
	char	*ps; //path_search

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
