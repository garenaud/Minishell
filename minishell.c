/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/24 14:08:59 by grenaud-         ###   ########.fr       */
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
	if (p->line == NULL)
		return (0);
	g_status = PARSING;
	if (p->line && ft_isprint(p->line[0]))
		add_history(p->line);
	return (p->line);
}

int	main(int argc, char *argv[], char *env[])
{
	t_parser		p;

	(void)argc;
	(void)argv;
	init_mini(&p, env);
	while (1)
	{
		p.line = set_and_get(&p);
 		if (p.line == NULL)
			break;
		reload(&p, env);
		parse_it(&p);
		run_shell(&p);
		clean_memory_parsing(&p);
	}
	delete_exeline(&p.cmd_exe);
	clean_memory_end(&p);
	return (0);
}
