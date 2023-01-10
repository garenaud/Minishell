/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:11:09 by jsollett          #+#    #+#             */
/*   Updated: 2022/12/21 10:18:25 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_value(t_dico *top, char *item)
{
	int	i;

	i = 0;
	while (top != NULL)
	{
		if ((ft_strncmp(top->value, item, ft_strlen(item)) == 0)
			&& (ft_strlen(top->value) == ft_strlen(item)))
			return (i);
		top = top->next;
		i++;
	}
	return (-1);
}

int	transfer_dico(t_dico **start, t_dico **end)
{
	t_dico	*tmp;

	tmp = NULL;
	if (size_stack_dico(*start) >= 1)
	{
		tmp = pop_dico(start);
		push_dico(end, tmp->key, tmp->value);
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return (1);
	}
	return (0);
}

int	remove_pos_dico(t_dico **top, size_t pos)
{
	t_dico	*tmp;
	t_dico	*c_tmp;

	tmp = NULL;
	c_tmp = NULL;
	if (pos >= size_stack_dico(*top))
		return (-1);
	else
	{
		while (pos > 0)
		{
			transfer_dico(top, &tmp);
			pos--;
		}
		c_tmp = pop_dico(top);
		free(c_tmp->key);
		free(c_tmp->value);
		free(c_tmp);
		while (tmp != NULL)
			transfer_dico(&tmp, top);
		return (0);
	}
}

t_dico	*reverse_dico(t_dico **top)
{
	t_dico	*tmp;
	t_dico	*c_tmp;

	tmp = NULL;
	while (*top != NULL)
	{
		c_tmp = NULL;
		c_tmp = pop_dico(top);
		push_dico(&tmp, c_tmp->key, c_tmp->value);
		free(c_tmp->key);
		free(c_tmp->value);
		free(c_tmp);
	}
	return (tmp);
}

t_dico	*getitem_dico(t_dico *top, size_t pos)
{
	t_dico	*tmp;

	tmp = malloc(sizeof(t_dico));
	if (!tmp)
		exit (-1);
	if (pos >= size_stack_dico(top))
		return (NULL);
	else
	{
		while (pos > 0)
		{
			top = top->next;
			pos--;
		}
		tmp->key = ft_strdup(top->key);
		tmp->value = ft_strdup(top->value);
		tmp->next = NULL;
		return (tmp);
	}
}
