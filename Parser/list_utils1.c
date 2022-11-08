/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:45:42 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/08 17:05:06 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push(t_list **top, char *item)
{
	t_list	*tmp;
	
//	printf("<%p>\n", *top);
	tmp = malloc(sizeof(t_list));
	if (!tmp)
		return;
//	printf("<%p> push\n", tmp);
	tmp->data = strdup(item);
	//free(item);//
//	printf("malloc push : %p\n", tmp);
	tmp->next = *top;
	*top = tmp; //?
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
	item = strdup(tmp->data); // semble pop leak
	*top = (*top)->next;
//	printf("<%p> strdup pop\n",item);
//	printf("<%p> free pop -data\n", tmp->data);
//	free(tmp->data);

//	printf("<%p> free pop -struct\n", tmp);
	free(tmp);
	return (item);
}

void	delete(t_list **top)
{
	t_list	*tmp;

	if (*top == NULL)
		return;
	while (*top != NULL)
	{
	
	 	tmp = *top;
		free(tmp->data);//
		*top = (*top)->next;
		
//	printf("<%p> free delete\n", tmp->data);
	//	free(tmp->data);

//	printf("<%p> free delete\n", tmp);
	free(tmp);
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

void	printll(t_list *lst)
{
	printf("start");
	while (lst)
	{
		printf("-->[%s]", (lst->data));
		lst = lst->next;
	}
	printf("-->[end]\n");
}
