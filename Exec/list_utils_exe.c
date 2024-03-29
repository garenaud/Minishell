/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_exe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:45:54 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/26 15:36:47 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exe	*init_exe_list(int size)
{
	t_exe	*new;

	new = (t_exe *)malloc(sizeof(t_exe));
	if (!new)
		return (NULL);
	new->pid = 0;
	new->redir = 0;
	new->path = NULL;
	new->error = 0;
	new->cmd_tab = ft_calloc(size + 2, sizeof(char *));
	new->fd_in = 0;
	new->fd_out = 0;
	new->next = NULL;
	return (new);
}

size_t	size_stack_exe(t_exe *top)
{
	size_t	size;

	size = 0;
	while (top != NULL)
	{
		size++;
		top = (top)->next;
	}
	return (size);
}

void	delete_exeline(t_exe **top)
{
	t_exe	*tmp;

	if (*top == NULL)
		return ;
	while (*top != NULL)
	{
		tmp = *top;
		if (tmp->cmd_tab != NULL)
			free_tab(tmp->cmd_tab);
		free(tmp->cmd_tab);
		free(tmp);
		*top = (*top)->next;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
}
