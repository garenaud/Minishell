/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:42:43 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/13 16:44:34 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmds(t_parser	*p)
{
	t_exe	*curr;
	t_exe	*next;

	curr = p->cmd_exe;
	while (curr)
	{
		next = curr->next;
		if (curr->cmd_tab)
		{
			free_tab(curr->cmd_tab);
			free(curr->cmd_tab);
		}
		free(curr);
		curr = next;
	}
}

int	free_all(t_parser *p)
{
	if (p->cmd_exe->cmd_tab != NULL)
	{
		free_tab(p->cmd_exe->cmd_tab);
		free(p->cmd_exe->cmd_tab);
	}
	return (0);
}
