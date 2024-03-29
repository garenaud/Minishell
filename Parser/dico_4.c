/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:35:18 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/17 15:44:15 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	duplicate(t_dico **orig, t_dico **copy)
{
	int		index;
	t_dico	*tmp;

	index = 0;
	while (index < (int)size_stack_dico(*orig))
	{
		tmp = NULL;
		tmp = getitem_dico(*orig, index);
		push_dico(copy, tmp->key, tmp->value);
		delete_dico(&tmp);
		index++;
	}
	*copy = reverse_dico(copy);
}
