/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:44:55 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/20 17:06:07 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		checknb_arg(t_dico *top)
{
	int	i;
	i = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->value,"|",1) == 0)
			return (i);
		top = top->next;
		i++;
	}
	return (i);	
}

int		checknb_pipe(t_dico *top)
{
	int i;
	i = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->value,"|",1) == 0)
			i++;
		top = top->next;
	}
	return (i);
}
