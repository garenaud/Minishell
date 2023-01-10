/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/09 15:47:57 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_parser	p;

	(void)argc;
	(void)argv;
	p.line = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
//	rl_catch_signals = 0;
	init_pgrm(&p, env);
	while ((p.line =readline("mini-->")))
	{
		init_pgrm(&p, env);
		get_path(&p, env);
		if (readline_manager(&p) == 1)
			break ;
		create_raw_list(&p.raw, p.line);
		p.raw = reverse(&p.raw);
		create_dico_list(&p.envvar, env);
		create_delim(&p);
		tester(&p);
		trim_list(&p.raw);
	//	check_for_envvar(&p);
		delete_int(&p.dquote);
		delete_int(&p.squote);
	//	check_quote_3(&p);
		{
			delete(&p.raw);
			delete_int(&p.flag);
			while (size_stack(p.util.raw_tmp))
			{
				transfer_c(&p.util.raw_tmp, &p.raw);
			}
			while (size_stack_int(p.util.code))
			{
				transfer_int(&p.util.code, &p.flag);
			}
			p.raw = reverse(&p.raw);
			p.flag = reverse_int(&p.flag);
		}
		cpd1(&p);
		printf(RED);
		printf("dico p.cmd_d\n");
		printll_dico(p.cmd_d);
		printf(ENDC);
		if (p.cmd_d)
		{
			create_path_access(&p);
			printll(p.struct_cmd.cmd);
		}
		printf(GREEN);
		printll(p.word);
		printf(ENDC);
		piping_main(&p);
		clean_memory_parsing(&p);
	}
	clean_memory_end(&p);
	return (0);
}
