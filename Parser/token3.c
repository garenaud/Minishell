/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:05:18 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/18 11:10:03 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	transfer_normal_char(t_parser *p)
{
	char	*c_tmp;
	int		count;

	count = 0;
	c_tmp = getitem_c(p->util.raw, 0);
	while (size_stack(p->util.raw) && getpos_c(p->util.delim, c_tmp) == -1)
	{
		transfer_c(&p->util.raw, &p->util.raw_tmp);
		push_int(&p->util.code, 0);
		count++;
	}
	return (count);
}

int	transfer_successive_c(t_list **start, t_list **end, char c)
{
	char	*c_tmp;
	int		count;

	count = 0;
	while (size_stack(*start) && ft_strncmp(getitem_c(*start, 0), &c, 1) == c)
	{
		c_tmp = pop(start);
		push(end, c_tmp);
		free(c_tmp);
		count++;
	}
	return (count);
}

void	get_inside_space1(t_parser *p)
{
	transfer_c(&p->util.raw, &p->util.raw_tmp);
	push_int(&p->util.code, 32);
	while (size_stack(p->util.raw)
		&& ft_strncmp(getitem_c(p->raw, 0), " ", 1) == 0)
	{
		remove_pos_c(&p->raw, 0);
	}
}

void	get_inside_space(t_parser *p)
{
	push(&p->util.tmp, p->util.c_tmp);
	push_int(&p->flag, 32);
	free(p->util.c_tmp);
	while (ft_strncmp(getitem_c(p->raw, 0), " ", 1) == 0)
	{
		remove_pos_c(&p->raw, 0);
	}
}
