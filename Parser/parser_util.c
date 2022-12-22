/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:31:49 by jsollett          #+#    #+#             */
/*   Updated: 2022/12/21 10:32:10 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_successive_key(t_parser *p)
{// ? ne check pas parite ' ou "
	int	count;
	int	index;

	count = 0;
	index = 0;
	while (index < (int)size_stack(p->raw))
	{
		if (ft_strncmp(getitem_c(p->raw, index), p->cmd_d_tmp->value, 1) == 0)
			count++;
		index++;
	}
	if (count % 2 == 0)
	{
		index = 0;
		while (index < (int)size_stack(p->raw))
		{
			if (ft_strncmp(getitem_c(p->raw, index), p->cmd_d_tmp->value, 1) == 0)
			{
				remove_pos_c(&p->raw, index);
			}
			index++;
		}
	}
	p->raw = reverse(&p->raw);
}
