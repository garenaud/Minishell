/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:56:16 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/11 10:21:16 by jsollett         ###   ########.fr       */
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

int	transfer_c(t_list **start, t_list **end)
{
	char	*c_tmp;
	
	if (size_stack(*start) >= 1)
	{
		c_tmp  = pop(start);
		push(end, c_tmp);
		free(c_tmp);
		return (1);
	}
	return (0);
}

int	remove_pos_c(t_list **top, size_t pos)
{//
	t_list	*tmp;
	char	*c_tmp;

	tmp = NULL;
	if (pos >= size_stack(*top))
		return (-1);
	else
	{
		while (pos > 0)
		{
			transfer_c(top, &tmp);
			pos--;
		}
		c_tmp = pop(top);
		free(c_tmp);
		while (tmp != NULL)
		{
			transfer_c(&tmp, top);
		}
		return (0);
	}
}

/*
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
*/
char	*getitem(t_list *top, size_t pos)
{// ok
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
