/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:16:04 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/06 14:50:10 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tester(t_parser *p)
{
	create_raw_list(&p->util.raw, p->line);
	p->util.raw = reverse(&p->util.raw);
	while (size_stack(p->util.raw))
	{
		if (ft_strncmp(getitem_c(p->util.raw, 0), "\'", 1) == 0)
			get_inside_squote2(p);
		if (ft_strncmp(getitem_c(p->util.raw, 0), "\"", 1) == 0)
			get_inside_dquote2(p);
		if (getpos_c(p->util.delim, getitem_c(p->util.raw, 0)) == -1)
			transfer_normal_char11(&p);
	}
	printf(RED"\n test token raw\n");
	printll(p->util.raw);
	printf(GREEN"\n test token raw_tmp\n");
	printll(p->util.raw_tmp);
	printf(ENDC"\n");
}
