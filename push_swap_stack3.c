/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_stack3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:57:59 by jsollett          #+#    #+#             */
/*   Updated: 2022/10/17 15:30:04 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	put_2end(t_list **a, t_list **b)
{
	if (size_stack(*a) >= 1 && size_stack(*b) >= 1)
	{
		put_end(a);
		put_end(b);
		return (1);
	}
	return (0);
}

int	getitem(t_list *top, size_t pos)
{
	if (pos >= size_stack(top))
		return (-1);
	else
	{
		while (pos > 0)
		{
			top = top->next;
			pos--;
		}
		return (top->a);
	}
}

int	getposition(t_list *top, int item)
{
	int	i;

	i = 0;
	while (top != NULL)
	{
		if (top->a == item)
			return (i);
		i++;
		top = top->next;
	}
	return (-1);
}

int	remove_position(t_list **top, size_t pos)
{
	t_list	*tmp;
	int		n;

	tmp = NULL;
	if (pos >= size_stack(*top))
		return (-1);
	else
	{
		while (pos > 0)
		{
			n = pop(top);
			push(&tmp, n);
			pos--;
		}
		n = pop(top);
		while (tmp != NULL)
		{
			n = pop(&tmp);
			push(top, n);
		}
		return (0);
	}
}

t_list	*reverse(t_list **top)
{
	t_list	*tmp;

	tmp = NULL;
	while (*top != NULL)
		push(&tmp, pop(top));
	return (tmp);
}
