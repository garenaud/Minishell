/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:03:29 by jsollett          #+#    #+#             */
/*   Updated: 2022/12/21 10:20:54 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_dico(t_dico **top, char *key, char *value)
{
	t_dico	*tmp;

	tmp = malloc(sizeof(t_dico));
	if (!tmp)
		return ;
	tmp->key = ft_strdup(key);
	tmp->value = ft_strdup(value);
	tmp->next = *top;
	*top = tmp;
}

t_dico	*pop_dico(t_dico **top)
{
	t_dico	*tmp;
	t_dico	*result;

	if (*top == NULL)
	{
		printf("pop Stack empty\n");
		return (NULL);
		exit (0);
	}
	result = malloc(sizeof(t_dico));
	if (!result)
		return (NULL);
	tmp = *top;
	result->key = ft_strdup(tmp->key);
	result->value = ft_strdup(tmp->value);
	*top = (*top)->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
	return (result);
}

void	delete_dico(t_dico **top)
{
	t_dico	*tmp;

	if (*top == NULL)
		return ;
	while (*top != NULL)
	{
		tmp = *top;
		*top = (*top)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

size_t	size_stack_dico(t_dico *top)
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

int	get_key(t_dico *top, char *item)
{
	int	i;

	i = 0;
	while (top != NULL)
	{
		if ((ft_strncmp(top->key, item, ft_strlen(top->key)) == 0)
			&& (ft_strlen(top->key) == ft_strlen(item)))
			return (i);
		top = top->next;
		i++;
	}
	return (-1);
}
