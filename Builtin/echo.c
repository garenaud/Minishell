/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:26:11 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/18 14:13:23 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bultin_echo(int i, t_exe *curr)
{
	while (curr->cmd_tab[i])
	{
		if (ft_strcmp(curr->cmd_tab[i], "$?") == 0){
			printf("impression $?");
			ft_putnbr_fd(g_status, 1);}
		else
		{
			ft_putstr_fd(curr->cmd_tab[i], 1);
			//printf("ECHO curr->cmd_tab[%d] = %s", i, curr->cmd_tab[i]);
		}
		if (curr->cmd_tab[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	return (0);
}

int	bultin_echo_n(t_exe *curr)
{
	int	i;

	i = 1;
	if (curr->cmd_tab[1] == NULL)
		write(1, "\n", 1);
	else
	{
		if (curr->cmd_tab[1][0] == '-' && curr->cmd_tab[1][1] == 'n')
		{
			i = 2;
			bultin_echo(i, curr);
		}
		else
		{
			bultin_echo(i, curr);
			write(1, "\n", 1);
		}
	}
	g_status = 0;
	return (0);
}
