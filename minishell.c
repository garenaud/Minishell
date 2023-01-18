/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/18 17:13:23 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_parser		p;
	struct termios	saved;

	(void)argc;
	(void)argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	init_mini(&p, env);
	p.line = readline("mini-->");
	while (p.line)
	{
		handle_signal(&saved);
		reload(&p, env);
		if (readline_manager(&p) == 1)
			break ;
		parse_it(&p);
		run_shell(&p);
		clean_memory_parsing(&p);
		p.line = readline("mini-->");
	}
	clean_memory_end(&p);
	return (0);
}
