/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:29:00 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/21 10:39:54 by jsollett         ###   ########.fr       */
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
	while (size_stack(*str) && ft_strncmp(getitem_c(*str, size_stack(*str) - 1), " ", 1) == 0)
		remove_pos_c(str, size_stack(*str) - 1);
}

void	trim_list_c(t_list **str, char *s)
{
	while (size_stack(*str) && ft_strncmp(getitem_c(*str, 0), s, 1) == 0)
		remove_pos_c(str, 0);
	while (size_stack(*str) && ft_strncmp(getitem_c(*str, size_stack(*str) - 1), s, 1) == 0)
		remove_pos_c(str, size_stack(*str) - 1);
}

char	*delimitateur(t_list **raw)
{
	if (ft_strncmp(getitem(*raw, 0), "\"", 1) == 0)
	{
		remove_pos_c(raw, 0);
		return ("\"");
	}
	else
	if (ft_strncmp(getitem(*raw, 0),"\'",1) == 0)
		{
			remove_pos_c(raw, 0);
			return ("\'");
		}
/* 	if (ft_strncmp(getitem(*raw, 0),":",1) == 0)
	{
		remove_pos_c(raw, 0);
		return (":");
	} */
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
