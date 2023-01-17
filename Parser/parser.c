/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:29:00 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/17 16:41:00 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getitem_c(t_list *top, size_t pos)
{
	if (pos >= size_stack(top))
		return (NULL);
	else
	{
		while (pos > 0)
		{
			top = top->next;
			pos--;
		}
		return (top->data);
	}
}

void	trim_list(t_list **str)
{
	while (size_stack(*str) && ft_strncmp(getitem_c(*str, 0), " ", 1) == 0)
		remove_pos_c(str, 0);
	while (size_stack(*str)
		&& ft_strncmp(getitem_c(*str, size_stack(*str) - 1), " ", 1) == 0)
		remove_pos_c(str, size_stack(*str) - 1);
}

char	*delimitateur(t_list **raw)
{
	if (ft_strncmp(getitem(*raw, 0), "\"", 1) == 0)
	{
		remove_pos_c(raw, 0);
		return ("\"");
	}
	else if (ft_strncmp(getitem(*raw, 0), "\'", 1) == 0)
	{
		remove_pos_c(raw, 0);
		return ("\'");
	}
	else
	{
		return (" ");
	}
}

char	*getpath(t_list **raw)
{
	int		i;
	int		pos;
	char	*str;
	char	*c_tmp;

	i = 0;
	pos = getpos_c(*raw, ":");
	if (pos == -1)
		pos = size_stack(*raw);
	str = malloc((pos +1) * sizeof(char));
	while (i < pos)
	{
		c_tmp = pop(raw);
		str[i] = *c_tmp;
		free(c_tmp);
		i++;
	}
	if (size_stack(*raw) != 0)
		remove_pos_c(raw, 0);
	str[i] = '\0';
	return (str);
}

void	create_parsing_dict(t_parser *p)
{
	while (size_stack(p->util.raw_tmp) && size_stack_int(p->util.code))
	{
		p->util.i1 = getitem_int(p->util.code, 0);
		p->util.i2 = p->util.i1;
		while (size_stack(p->util.raw_tmp) && p->util.i2 != 32)
		{
			p->util.c_tmp = pop(&p->util.raw_tmp);
			push(&p->util.tmp, p->util.c_tmp);
			free(p->util.c_tmp);
			p->util.i2 = pop_int(&p->util.code);
			p->util.i2 = getitem_int(p->util.code, 0);
		}
		p->util.tmp = reverse(&p->util.tmp);
		p->util.c_tmp = getall(&p->util.tmp);
		cpd1_key(p);
		if (ft_strlen(p->util.c_tmp))
			push_dico(&p->cmd_d, p->util.key, p->util.c_tmp);
		free(p->util.c_tmp);
		remove_position_int(&p->util.code, 0);
		remove_pos_c(&p->util.raw_tmp, 0);
		delete(&p->util.tmp);
	}
	p->cmd_d = reverse_dico(&p->cmd_d);
}
