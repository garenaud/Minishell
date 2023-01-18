/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:46:05 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/18 11:24:03 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bultin_unset(t_exe *curr, t_parser *p)
{
	int		pos;

	p->built.i = 1;
	if (curr->cmd_tab[p->built.i])
	{
		while (curr->cmd_tab[p->built.i])
		{
			pos = get_key(p->envvar, curr->cmd_tab[p->built.i]);
			if (pos != -1)
			{
				remove_pos_dico(&p->envvar, pos);
			}
			p->built.i++;
		}
	}
	g_status = 0;
	return (0);
}
