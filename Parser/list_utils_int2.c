/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_int2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:57:35 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/17 15:57:47 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	size_stack_int(t_list_i *top)
{
	size_t	size;

	size = 0;
	while (top != NULL)
	{
		size++;
		top = (top)->next;
	}
	return (size);
}

int	remove_position_int(t_list_i **top, size_t pos)
{
	t_list_i	*tmp;
	int			n;

	tmp = NULL;
	if (pos >= size_stack_int(*top))
		return (-1);
	else
	{
		while (pos > 0)
		{
			n = pop_int(top);
			push_int(&tmp, n);
			pos--;
		}
		n = pop_int(top);
		while (tmp != NULL)
		{
			n = pop_int(&tmp);
			push_int(top, n);
		}
		return (0);
	}
}

int	getitem_int(t_list_i *top, size_t pos)
{
	if (pos >= size_stack_int(top))
		return (-1);
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
