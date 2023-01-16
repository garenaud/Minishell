/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/16 17:05:51 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_parser	p;

	(void)argc;
	(void)argv;
	p.line = NULL;
	g_status = 0;
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
		init_parsing_list_c(&p);
		delete_parsing_list_c(&p);
		create_dico_list(&p.envvar, env);
		//printf("\nentree tester\n");
		create_delim(&p);
		{// test de la partie token
			tester(&p);
		}
		trim_list(&p.raw);
		check_for_envvar(&p);
		//printf("--------fin envvar--------\n");
		delete_int(&p.dquote);
		delete_int(&p.squote);
		init_parsing_list_c(&p);
		delete_parsing_list_c(&p);
		check_quote_3(&p);
	//    check_for_envvar(&p);
		//printf("--------fin quote 3--------\n");
		//create_parsing_dico(&p);
		cpd1(&p);
		//p.cmd_d = reverse_dico(&p.cmd_d);
		//printf(RED);
		//printf("dico p.cmd_d\n");
		//printll_dico(p.cmd_d);
		//printf(ENDC);
		//init_parsing_list(&p);
		if (p.cmd_d)
		{
			create_path_access(&p);
			//printll(p.struct_cmd.cmd);
		}
		//printll_exe(p.cmd_exe->cmd_tab);
		//printf(GREEN);
		//printll(p.word);
		//printf(ENDC);
		//piping_main(&p);
		run_shell(&p);
		//exec(&p, p.cmd_exe);
		clean_memory_parsing(&p);
	}
	printf(RED"----------------- sortie prgm ----------------\n"ENDC);
	clean_memory_end(&p);
	return (0);
}
