/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:26:11 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/21 16:50:36 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_cmd *e)
{
	int	nb_arg;
	int	i;

	nb_arg = size_stack(e->arg);
	i = 0;
	if (nb_arg == 0)
	{
		if (strncmp(e->option, "-n", 2) == 0)
			return (1);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	while (i <= nb_arg + 1)
	{
		ft_putstr_fd(getitem_c(e->arg, i), 1);
		ft_putchar_fd(" ", 1);
		i++;
	}
	if (strncmp(e->option, "-n", 2) == 0)
		return (1);
	else
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	return (1);
}
