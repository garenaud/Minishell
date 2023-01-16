/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:05:08 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/12 13:58:58 by jsollett         ###   ########.fr       */
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
// count successive char ?
int	c_s_c(t_parser *p, char *c)
{
	int	count;
	int	index;

	count = 0;
	index = 0;
	while (index < (int)size_stack(p->util.raw) && ft_strncmp(getitem_c(p->util.raw, index), c, 1) == 0)
	{
		count++;
		index++;
	}
	return (count);
}

void	get_inside_space1(t_parser *p)
{
	transfer_c(&p->util.raw, &p->util.raw_tmp);
	push_int(&p->util.code, 32);
	while (size_stack(p->util.raw) && ft_strncmp(getitem_c(p->raw, 0), " ", 1) == 0)
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

// transfer avec space le > | <
void	transfer_char_space(t_parser *p)
{
	char	c[3];

	if (ft_strncmp(getitem_c(p->util.raw, 0), "\"", 1) == 0
		|| ft_strncmp(getitem_c(p->util.raw, 0), "\'", 1) == 0)
		return ;
	if (ft_strncmp(getitem_c(p->util.raw_tmp, 0), " ", 1)
		&& ft_strncmp(getitem_c(p->util.raw, 0), "=", 1))
	{
		push_int(&p->util.code, 32);
		push(&p->util.raw_tmp, " ");
	}
	if (c_s_c(p, "|") == 2 || c_s_c(p, "<") == 2 || c_s_c(p, ">") == 2)
	{
		c[0] = *getitem_c(p->util.raw, 0);
		c[1] = c[0];
		c[2] = '\0';
		push_int(&p->util.code, get_code_s(c));
		push_int(&p->util.code, get_code_s(c));
		transfer_c(&p->util.raw, &p->util.raw_tmp);
		transfer_c(&p->util.raw, &p->util.raw_tmp);
	}
	else if (c_s_c(p, "|") == 1 || c_s_c(p, "<") == 1 || c_s_c(p, ">") == 1 || c_s_c(p, "=") == 1)
	{
		push_int(&p->util.code, get_code_c1(p, getitem_c(p->util.raw, 0)));
		transfer_c(&p->util.raw, &p->util.raw_tmp);
	}
	else
		perror("syntax erreur\n");
	if (ft_strncmp(getitem_c(p->util.raw, 0), " ", 1)
		&& ft_strncmp(getitem_c(p->util.raw_tmp, 0), "=", 1))
	{
		push(&p->util.raw_tmp, " ");
		push_int(&p->util.code, 32);
	}
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

// a tester regle 1 peut etre mettre expand $ et enlever $ delim
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
