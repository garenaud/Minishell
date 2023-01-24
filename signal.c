/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:00:52 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/24 12:19:31 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		if (g_status != WORKING)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		if (g_status == WORKING)
		{
			write(1, "^C\n", 3);
			g_status = 130;
		}
	}
	if (signo == SIGQUIT)
	{
		if (g_status == WORKING)
		{
			g_status = 131;
			printf("^\\Quit: 3\n");
		}
	}
}

int	set_signal(void)
{
	if (signal(SIGINT, handle_signals) == SIG_ERR)
	{
		printf("failed to register signal\n");
		return (0);
	}
	if (signal(SIGQUIT, handle_signals) == SIG_ERR)
	{
		printf("failed to register signal\n");
		return (0);
	}
	return (1);
}

void	setup_term(struct termios *show)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, show);
	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}
