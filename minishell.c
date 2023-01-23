/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/23 14:10:39 by jsollett         ###   ########.fr       */
=======
/*   Updated: 2023/01/23 14:03:28 by grenaud-         ###   ########.fr       */
>>>>>>> 4639d53d0173a8089573155f55a5963cddb48b0e
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_and_get(t_parser *p)
{
	p->line = NULL;
	p->piped = 0;
	if (g_status > 4)
		p->return_val = g_status;
	g_status = WAITING;
	signal(SIGQUIT, SIG_IGN);
	p->line = readline(BLUE"mini--> "ENDC);
	g_status = PARSING;
	if (p->line && ft_isprint(p->line[0]))
		add_history(p->line);
	return (p->line);
}

int	main(int argc, char *argv[], char *env[])
{
	t_parser		p;
	//struct termios	saved;

	(void)argc;
	(void)argv;
	init_mini(&p, env);
	while (1)
	{
		p.line = set_and_get(&p);
		//printf("return val = %d g_status = %d\n", p.return_val, g_status);
		if (p.line == NULL)
			return (0);
		//handle_signal(&saved);
		reload(&p, env);
/* 		if (readline_manager(&p) == 1)
			break ; */
		parse_it(&p);
		run_shell(&p);
		clean_memory_parsing(&p);
	}
	delete_exeline(&p.cmd_exe);
	clean_memory_end(&p);
	return (0);
}
