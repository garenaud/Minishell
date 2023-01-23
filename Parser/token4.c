/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:18:59 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/23 10:23:13 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_helper(t_parser *p)
{
	p->util.pos = 0;
	p->util.pos1 = 0;
	remove_pos_c(&p->util.raw, 0);
}

void	get_inside_dquote2(t_parser *p)
{
	char	*c_tmp;

	init_helper(p);
	while (ft_strncmp(getitem_c(p->util.raw, 0), "\"", 1) != 0)
	{
		if (ft_strncmp(getitem_c(p->util.raw, 0), "$", 1) == 0)
		{
			transfer_normal_char_helper1(p, 0);
			while (ft_isalnum(getitem_c(p->util.raw, 0)[0]))
			{
				c_tmp = getitem_c(p->util.raw, 0);
				transfer_c(&p->util.raw, &p->util.key_l);
				if (ft_isnum(*c_tmp, p->util.pos) == -1)
					break ;
				p->util.pos++;
			}
			p->util.code_nb = 2;
			expand_to_value(p);
			continue ;
		}
		p->util.pos1++;
		transfer_helper_1(p, 2);
	}
	get_inside_dq(p, p->util.pos1);
}
