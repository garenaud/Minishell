/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:09:44 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/16 17:27:53 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strtolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
}

int	is_builtin(char **str)
{
	ft_strtolower(str[0]);
	if (str[0] == 0)
		return (0);
	if (!ft_strcmp(str[0], "echo")
		|| !ft_strcmp(str[0], "pwd")
		|| !ft_strncmp(str[0], ".", 1)
		|| !ft_strcmp(str[0], "env")
		|| !ft_strcmp(str[0], "exit")
		|| !ft_strcmp(str[0], "cd")
		|| !ft_strcmp(str[0], "export")
		|| !ft_strcmp(str[0], "unset")
		|| !ft_strncmp(str[0], "/", 1))
	{
		return (1);
	}
	return (-1);
}

int	bultin_search(t_exe *curr)
{
	ft_strtolower(curr->cmd_tab[0]);
	if (ft_strcmp(curr->cmd_tab[0], "echo") == 0)
		return (bultin_echo_n(curr));
	else if (ft_strcmp(curr->cmd_tab[0], "cd") == 0)
		return (bultin_cd(curr));
	else if (ft_strcmp(curr->cmd_tab[0], "pwd") == 0)
		printf("encore a faire\n");
	if (ft_strcmp(curr->cmd_tab[0], "export") == 0)
		printf("encore a faire\n");
	if (ft_strcmp(curr->cmd_tab[0], "unset") == 0)
		printf("encore a faire\n");
	if (ft_strcmp(curr->cmd_tab[0], "env") == 0)
		printf("encore a faire\n");
	if (ft_strcmp(curr->cmd_tab[0], "exit") == 0)
		printf("encore a faire\n");
	printf("bultin_search n'a rien donne\n");
	return (0);
}
