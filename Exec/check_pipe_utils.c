/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:44:55 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/26 15:25:49 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checknb_arg_calloc(t_dico *top)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->value, "|", 1) == 0)
			return (i);
		if (is_redir(top->key) == 1)
		{
			j++;
			if (top->next != NULL || ft_strncmp(top->next->value, "|", 1) != 0)
				j++;
		}
		top = top->next;
		i++;
	}
	if (i < j)
		i = 0;
	else
		i = i - j;
	return (i);
}

int	checknb_redir(t_dico *top)
{
	int	i;

	i = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->value, "|", 1) == 0)
			return (i);
		if (is_redir(top->key) == 1)
		{
			i += 2;
			if (top->next != NULL)
				top = top->next;
		}
		top = top->next;
	}
	return (i);
}

int	checknb_arg(t_dico *top, t_parser *p)
{
	int	i;

	i = 0;
	if (size_stack_dico(top) == 0)
		return (0);
	if (ft_strncmp(top->value, "|", 1) == 0)
	{
		printf ("Minishell: syntax error near unexpected token `|'\n");
		p->return_val = 258;
		return (1);
	}
	while (top != NULL)
	{
		if (ft_strncmp(top->value, "|", 1) == 0)
			return (i);
		top = top->next;
		i++;
	}
	return (i);
}

int	checknb_pipe(t_dico *top, t_parser *p)
{
	int	i;

	i = 0;
	while (top != NULL)
	{
		if (top->next != NULL && is_redir(top->key) == 1
			&& ft_strncmp(top->next->value, "|", 1) == 0)
		{
			printf ("Minishell: syntax error near unexpected token `|'\n");
			p->return_val = 258;
			delete_dico(&top);
			return (0);
		}
		if (ft_strncmp(top->value, "|", 1) == 0)
			i++;
		top = top->next;
	}
	return (i);
}
