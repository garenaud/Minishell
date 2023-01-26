/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:33:39 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/26 16:34:21 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_help(t_parser *p)
{
	if (size_stack_dico(p->cmd_d) == 0)
	{
		p->error = -1;
		return ;
	}
	if (ft_strncmp(p->cmd_d->key, "5", 1) == 0)
	{
		p->error = -5;
		return ;
	}
	p->error = 1;
}

void	check_succ_redir(t_parser *p)
{
	t_dico	*tmp;
	int		index;

	tmp = NULL;
	index = 0;
	while (index < (int) size_stack_dico(p->cmd_d))
	{
		tmp = getitem_dico(p->cmd_d, index);
		if ((ft_strncmp(tmp->key, "4", 1) == 0
				|| ft_strncmp(tmp->key, "3", 1) == 0)
			&& ft_strlen(tmp->value) > 2)
			p->error = -4;
		delete_dico(&tmp);
		index++;
	}
}
