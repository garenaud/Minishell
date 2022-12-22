/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:46:31 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/21 10:28:37 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_int(t_list_i **top, int item)
{
	t_list_i	*tmp;

	tmp = malloc(sizeof(t_list_i));
	if (!tmp)
		return ;
	tmp->data = item;
	tmp->next = *top;
	*top = tmp;
}

int	pop_int(t_list_i **top)
{
	t_list_i	*tmp;
	int			item;

	if (*top == NULL)
	{
		printf("Stack empty\n");
		exit (0);
	}
	tmp = *top;
	item = tmp->data;
	*top = (*top)->next;
	free(tmp);
	return (item);
}

void	delete_int(t_list_i **top)
{
	t_list_i	*tmp;

	if (*top == NULL)
		return ;
	while (*top != NULL)
	{
		tmp = *top;
		*top = (*top)->next;
		free(tmp);
	}
}

t_list_i	*reverse_int(t_list_i **top)
{
	t_list_i	*tmp;

	tmp = NULL;
	while (*top != NULL)
		push_int(&tmp, pop_int(top));
	return (tmp);
}

void	printll_int(t_list_i *lst)
{
	printf("start");
	while (lst)
	{
		printf("-->[%d]", (lst->data));
		lst = lst->next;
	}
	printf("-->[end]\n");
}
