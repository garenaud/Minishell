/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:16:04 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/18 11:21:59 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tester(t_parser *p)
{
	create_raw_list(&p->util.raw, p->line);
	p->util.raw = reverse(&p->util.raw);
	while (size_stack(p->util.raw))
	{
		if (size_stack(p->util.raw)
			&& ft_strncmp(getitem_c(p->util.raw, 0), "\'", 1) == 0)
			get_inside_squote2(p);
		if (size_stack(p->util.raw)
			&& ft_strncmp(getitem_c(p->util.raw, 0), "\"", 1) == 0)
			get_inside_dquote2(p);
		if (size_stack(p->util.raw)
			&& getpos_c(p->util.delim, getitem_c(p->util.raw, 0)) == -1)
			transfer_normal_char1(p);
		if (size_stack(p->util.raw)
			&& ft_strncmp(getitem_c(p->util.raw, 0), " ", 1) == 0)
			get_inside_space1(p);
		if (size_stack(p->util.raw)
			&& getpos_c(p->util.delim, getitem_c(p->util.raw, 0)) != -1)
			transfer_char_space(p);
	}
	p->util.raw_tmp = reverse(&p->util.raw_tmp);
	p->util.code = reverse_int(&p->util.code);
}
