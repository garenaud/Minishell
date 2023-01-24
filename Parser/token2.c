/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:04:18 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/24 10:53:45 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	transfer_helper_1(t_parser *p, int code)
{
	transfer_c(&p->util.raw, &p->util.raw_tmp);
	push_int(&p->util.code, code);
}

void	transfer_normal_char_helper1(t_parser *p, int code)
{
	int	count;

	count = c_s_c(p, "$");
	while (count - 1)
	{
		transfer_c(&p->util.raw, &p->util.raw_tmp);
		push_int(&p->util.code, code);
		count--;
	}
	if (size_stack(p->util.raw) == 1)
		transfer_helper_1(p, code);
	else
	{
		if (ft_isalnum(getitem_c(p->util.raw, 1)[0]))
			remove_pos_c(&p->util.raw, 0);
		else
		{
			transfer_c(&p->util.raw, &p->util.raw_tmp);
			push_int(&p->util.code, code);
		}
	}
}

void	transfer_normal_char1(t_parser *p)
{
	char	*c_tmp;
	int		pos;

	pos = 0;
	while (size_stack(p->util.raw)
		&& getpos_c(p->util.delim, getitem_c(p->util.raw, 0)) == -1)
	{
		if (ft_strncmp(getitem_c(p->util.raw, 0), "$", 1) == 0)
		{
			transfer_normal_char_helper1(p, 0);
			while (size_stack(p->util.raw)
				&& ft_isalnum(getitem_c(p->util.raw, 0)[0]))
			{
				c_tmp = getitem_c(p->util.raw, 0);
				transfer_c(&p->util.raw, &p->util.key_l);
				if (ft_isnum(*c_tmp, pos) == -1)
					break ;
				pos++;
			}
			p->util.code_nb = 0;
			expand_to_value(p);
			continue ;
		}
		transfer_helper_1(p, 0);
	}
}

void	get_inside_squote2(t_parser *p)
{
	remove_pos_c(&p->util.raw, 0);
	while (size_stack(p->util.raw)
		&& ft_strncmp(getitem_c(p->util.raw, 0), "'\'", 1) != 0)
	{
		transfer_c(&p->util.raw, &p->util.raw_tmp);
		push_int(&p->util.code, 1);
	}
	remove_pos_c(&p->util.raw, 0);
}

void	get_inside_dq(t_parser *p, int pos1)
{
	if (pos1 == 0)
	{
		push(&p->util.raw_tmp, " ");
		push_int(&p->util.code, 2);
	}
	remove_pos_c(&p->util.raw, 0);
}
