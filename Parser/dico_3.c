/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:24:29 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/17 15:42:39 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_dico_32(t_parser **p, t_list **raw_tmp, t_list_i **flag_tmp)
{
	char	*tmp;
	int		flag;

	tmp = pop(&(*p)->raw);
	push(&(*raw_tmp), tmp);
	free(tmp);
	flag = pop_int(&(*p)->flag);
	push_int(&(*flag_tmp), flag);
	while (getitem_int((*p)->flag, 0) == 32)
	{
		remove_position_int(&(*p)->flag, 0);
		remove_pos_c(&(*p)->raw, 0);
	}
}

void	clean_dico_helper(t_parser **p, t_list **raw_tmp, t_list_i **flag_tmp)
{
	char	*tmp;
	int		flag;

	tmp = pop(&(*p)->raw);
	push(&(*raw_tmp), tmp);
	free(tmp);
	flag = pop_int(&(*p)->flag);
	push_int(&(*flag_tmp), flag);
}

void	clean_dico(t_parser *p)
{
	t_list		*raw_tmp;
	t_list_i	*flag_tmp;

	raw_tmp = NULL;
	flag_tmp = NULL;
	while (size_stack(p->raw))
	{
		if (getitem_int(p->flag, 0) == 32)
		{
			clean_dico_32(&p, &raw_tmp, &flag_tmp);
		}
		else
		{
			clean_dico_helper(&p, &raw_tmp, &flag_tmp);
		}
	}
	p->raw = reverse(&raw_tmp);
	p->flag = reverse_int(&flag_tmp);
}

size_t	find_min_key(t_dico *dico)
{
	size_t	min;
	size_t	index;
	t_dico	*tmp;
	char	*s;

	index = 0;
	min = 0;
	s = ft_strdup("zzzz");
	while (index < size_stack_dico(dico))
	{
		tmp = getitem_dico(dico, index);
		if (ft_strcmp(tmp->key, s) < 0)
		{
			free(s);
			s = ft_strdup(tmp->key);
			min = index;
		}
		delete_dico(&tmp);
		index++;
	}
	free(s);
	return (min);
}

size_t	find_max_key(t_dico *dico)
{
	size_t	min;
	size_t	index;
	t_dico	*tmp;
	char	*s;

	index = 0;
	min = 0;
	s = ft_strdup("");
	while (index < size_stack_dico(dico))
	{
		tmp = getitem_dico(dico, index);
		if (ft_strcmp(s, tmp->key) < 0)
		{
			free(s);
			s = ft_strdup(tmp->key);
			min = index;
		}
		delete_dico(&tmp);
		index++;
	}
	free(s);
	return (min);
}
