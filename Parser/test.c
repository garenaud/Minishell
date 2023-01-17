/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:55:24 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/17 17:20:05 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void cpd1_key(t_parser *p)
{
	if (p->util.i1 == 0)
		p->util.key = "0";
	if (p->util.i1 == 1)
		p->util.key = "1";
	if (p->util.i1 == 2)
		p->util.key = "2";
	if (p->util.i1 == 3)
		p->util.key = "3";
	if (p->util.i1 == 4)
		p->util.key = "4";
	if (p->util.i1 == 5)
		p->util.key = "5";
	if (p->util.i1 == 6)
		p->util.key = "6";
	if (p->util.i1 == 7)
		p->util.key = "7";
	if (p->util.i1 == 8)
		p->util.key = "8";
}

void	cpd1(t_parser *p)
{
	while (size_stack(p->raw) && size_stack_int(p->flag))
	{
		p->util.i1 = getitem_int(p->flag, 0);
		p->util.i2 = p->util.i1;
		while (size_stack(p->raw) && p->util.i2 != 32)
		{
			p->util.c_tmp = pop(&p->raw);
			push(&p->util.tmp, p->util.c_tmp);
			free(p->util.c_tmp);
			p->util.i2 = pop_int(&p->flag);
			p->util.i2 = getitem_int(p->flag, 0);
		}
		p->util.tmp = reverse(&p->util.tmp);
		p->util.c_tmp = getall(&p->util.tmp);
		cpd1_key(p);
		if (ft_strlen(p->util.c_tmp))
			push_dico(&p->cmd_d, p->util.key, p->util.c_tmp);
		free(p->util.c_tmp);
		remove_position_int(&p->flag, 0);
		remove_pos_c(&p->raw, 0);
		delete(&p->util.tmp);
	}
	p->cmd_d = reverse_dico(&p->cmd_d);
}
