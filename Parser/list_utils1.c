/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:45:42 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/21 10:30:41 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push(t_list **top, char *item)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (!tmp)
		return ;
	tmp->data = strdup(item);
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
		//return (NULL);
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

void	printll(t_list *lst)
{
	printf("start");
	while (lst)
	{
		printf("-->[%s]\n", (lst->data));
		lst = lst->next;
	}
	printf("-->[end]\n");
}

void	print_ic(t_list_i *lst_i, t_list *lst)
{
	printf("start\n");
	while (lst && lst_i)
	{
		printf("[%d]-->[%s]\n",(lst_i->data), (lst->data));
		lst = lst->next;
        lst_i = lst_i->next;
	}
	printf("-->[end]\n");
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
