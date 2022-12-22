/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:46:36 by jsollett          #+#    #+#             */
/*   Updated: 2022/12/21 10:47:04 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	getposition(t_list *top, char *item)
{
	int	i;
	int	len;

	len = ft_strlen(item);
	i = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->data, item, len) == 0)
			return (i);
		i++;
		top = top->next;
	}
	return (-1);
}
