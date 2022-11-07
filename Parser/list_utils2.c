/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:56:16 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/04 18:22:52 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_adr(t_list *lst)
{
	printf("start");
	while (lst)
	{
		printf("-->[%p]", (lst));
		lst = lst->next;
	}
	printf("-->[end]\n");
}

size_t	size_stack(t_list *top)
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

int	remove_position(t_list **top, size_t pos)
{
	t_list	*tmp;
	char	*n;

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

char	*getitem(t_list *top, size_t pos)
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
