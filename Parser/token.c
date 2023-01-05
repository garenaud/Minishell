/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:05:08 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/05 15:16:20 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_successive_c(t_parser *p, char *c)
{
	int	count;
	int	index;

	count = 1;
	index = 0;
	while (index < (int)size_stack(p->raw) && ft_strncmp(getitem_c(p->raw, index), c, 1) == 0)
	{
		count++;
		index++;
	}
	return (count);
}

//a verifier
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

// transfer avec space le > | <
void	transfer_char_space(t_parser *p)
{// semble ok
	push_int(&p->util.code, 32);
	push(&p->util.raw_tmp, " ");
	push_int(&p->util.code, get_code_c(p, *getitem_c(p->util.raw, 0)));
	transfer_c(&p->util.raw, &p->util.raw_tmp);
	push(&p->util.raw_tmp, " ");
	push_int(&p->util.code, 32);
}

// a tester
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

// a tester regle 1
int	transfer_normal_char(t_parser *p)
{
	char	*c_tmp;
	int		count;

	count = 0;
	c_tmp = getitem_c(p->util.raw, 0);
	while (size_stack(p->util.raw) && getpos_c(p->util.delim, c_tmp) == -1)
	{
		push_int(&p->util.code, 0);
		transfer_c(&p->util.raw, &p->util.raw_tmp);
		count++;
	}
	return (count);
}
