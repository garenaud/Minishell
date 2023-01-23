/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:05:08 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/23 13:58:53 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	c_s_c(t_parser *p, char *c)
{
	int	count;
	int	index;

	count = 0;
	index = 0;
	while (index < (int)size_stack(p->util.raw)
		&& ft_strncmp(getitem_c(p->util.raw, index), c, 1) == 0)
	{
		count++;
		index++;
	}
	return (count);
}

static void	push_2(t_parser *p, char *s, int code)
{
	push_int(&p->util.code, code);
	push(&p->util.raw_tmp, s);
}

static void	transfer_helper(t_parser *p)
{
	char	s[3];

	s[0] = *getitem_c(p->util.raw, 0);
	s[1] = s[0];
	s[2] = '\0';
	push_int(&p->util.code, get_code_s(s));
	push_int(&p->util.code, get_code_s(s));
	transfer_c(&p->util.raw, &p->util.raw_tmp);
	transfer_c(&p->util.raw, &p->util.raw_tmp);
}
// transfer avec space le > | <

void	transfer_char_space(t_parser *p)
{
	int	nfold;

	if (ft_strncmp(getitem_c(p->util.raw, 0), "\"", 1) == 0
		|| ft_strncmp(getitem_c(p->util.raw, 0), "\'", 1) == 0)
		return ;
	if (ft_strncmp(getitem_c(p->util.raw_tmp, 0), " ", 1)
		&& ft_strncmp(getitem_c(p->util.raw, 0), "=", 1))
		push_2(p, " ", 32);
	if (c_s_c(p, "|") == 2 || c_s_c(p, "<") == 2 || c_s_c(p, ">") == 2)
		transfer_helper(p);
	else if (c_s_c(p, "|") == 1 || c_s_c(p, "<") == 1
		|| c_s_c(p, ">") == 1 || c_s_c(p, "=") == 1)
	{
		push_int(&p->util.code, code1(p, getitem_c(p->util.raw, 0)));
		transfer_c(&p->util.raw, &p->util.raw_tmp);
	}
	else
	{
		nfold = tsc(&p->util.raw, &p->util.raw_tmp, *getitem_c(p->util.raw, 0));
		while (nfold--)
			push_int(&p->util.code, code1(p, getitem_c(p->util.raw_tmp, 0)));
	}
/* 	else
		perror("syntax erreur\n"); */
	if (ft_strncmp(getitem_c(p->util.raw, 0), " ", 1)
		&& ft_strncmp(getitem_c(p->util.raw_tmp, 0), "=", 1))
		push_2(p, " ", 32);
}
