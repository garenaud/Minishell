/*  ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:04:18 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/06 15:25:29 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	transfer_normal_char1(t_parser *p)
{
	char	*c_tmp;

	c_tmp = getitem_c(p->util.raw, 0);
	while (size_stack(p->util.raw) && getpos_c(p->util.delim, getitem_c(p->util.raw, 0)) == -1)
	{
		if (ft_strncmp(getitem_c(p->util.raw, 0), "$", 1) == 0)
		{
			remove_pos_c(&p->util.raw, 0);
			while (size_stack(p->util.raw) && ft_isalnum(getitem_c(p->util.raw, 0)[0]))
			{
				transfer_c(&p->util.raw, &p->util.key_l);
			}
			p->util.code_nb = 0;
			expand_to_value(p);
			continue ;
		}
		transfer_c(&p->util.raw, &p->util.raw_tmp);
		push_int(&p->util.code, 0);
	}
}

void	transfer_normal_char11(t_parser **p)
{
	char	*c_tmp;

	c_tmp = getitem_c((*p)->util.raw, 0);
	while (size_stack((*p)->util.raw) && getpos_c((*p)->util.delim, c_tmp) == -1)
	{
		if (ft_strncmp(getitem_c((*p)->util.raw, 0), "$", 1) == 0)
		{
			remove_pos_c(&(*p)->util.raw, 0);
			while (size_stack((*p)->util.raw) && ft_isalnum(getitem_c((*p)->util.raw, 0)[0]))
			{
				transfer_c(&(*p)->util.raw, &(*p)->util.key_l);
			}
			expand_to_value((*p));
			continue ;
		}
		transfer_c(&(*p)->util.raw, &(*p)->util.raw_tmp);
		push_int(&(*p)->util.code, 0);
	}
}

void	get_inside_squote2(t_parser *p)
{
	remove_pos_c(&p->util.raw, 0);

	while (size_stack(p->util.raw) && ft_strncmp(getitem_c(p->util.raw, 0), "'\'", 1) != 0)
	{
		transfer_c(&p->util.raw, &p->util.raw_tmp);
		push_int(&p->util.code, 1);
	}
	remove_pos_c(&p->util.raw, 0);
}
