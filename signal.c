/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:00:52 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/12 15:49:10 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		write (1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signal(struct termios *saved)
{
	hide_key(saved);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	hide_key(struct termios *saved)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	tcgetattr(STDIN_FILENO, saved);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);
}

void	handle_sigquit(int signum)
{
	if (signum == SIGINT)
	{
		write (1, "\n", 1);
	}
	if (signum == SIGQUIT)
	{
		printf("Quit: 3\n");
		rl_on_new_line();
	}
}