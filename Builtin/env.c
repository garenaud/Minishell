/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:50:13 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/16 14:25:17 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bultin_env(t_exe *curr, t_parser *p)
{
	int		index;
	t_dico	*tmp;

	p->built.i = 1;
	index = 0;
	if (curr->cmd_tab[p->built.i] == NULL)
	{
		while (index < (int)size_stack_dico(p->envvar))
		{
			tmp = getitem_dico(p->envvar, index);
			printf("%s=%s\n", (tmp->key), (tmp->value));
			delete_dico(&tmp);
			index++;
		}
	}
	g_status = 0;
	return (0);
}
