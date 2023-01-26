/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:45:42 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/26 14:01:25 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push(t_list **top, char *item)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (!tmp)
		return ;
	tmp->data = ft_strdup(item);
	tmp->next = *top;
	*top = tmp;
}

char	*pop(t_list **top)
{
	t_list	*tmp;
	char	*item;

	if (*top == NULL)
	{
		printf("Stack empty\n");
		exit (0);
	}
	tmp = *top;
	item = ft_strdup(tmp->data);
	*top = (*top)->next;
	free(tmp->data);
	free(tmp);
	return (item);
}

void	delete(t_list **top)
{
	t_list	*tmp;

	if (*top == NULL)
		return ;
	while (*top != NULL)
	{
		tmp = *top;
		*top = (*top)->next;
		free(tmp->data);
		free(tmp);
	}
}

t_list	*reverse(t_list **top)
{
	t_list	*tmp;
	char	*c_tmp;

	tmp = NULL;
	while (*top != NULL)
	{
		c_tmp = pop(top);
		push(&tmp, c_tmp);
		free(c_tmp);
	}
	return (tmp);
}

int	getpos_c(t_list *top, char *item)
{
	int	i;

	i = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->data, item, ft_strlen(item)) == 0)
			return (i);
		top = top->next;
		i++;
	}
	return (-1);
}
