/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/06 16:31:24 by grenaud-         ###   ########.fr       */
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
	rl_catch_signals = 0;
	init_pgrm(&p, env);// ne pas le deplacer
	//get_path(&p, env);
	while ((p.line = readline("mini--> ")))
	{
		//init_pgrm(&p, env);
		//printll(p.struct_path.split_path);
		init_pgrm(&p, env);
		get_path(&p, env);
		if (readline_manager(&p) == 1)
			break ;
	//	printll(p.struct_path.split_path);
		/* init_pgrm(&p, env);
		get_path(&p, env); */
		create_raw_list(&p.raw, p.line);
		p.raw = reverse(&p.raw);

		init_parsing_list_c(&p);
		delete_parsing_list_c(&p);
		create_dico_list(&p.envvar, env);
		trim_list(&p.raw);
		check_for_envvar(&p);
		printf("--------fin envvar--------\n");
		delete_int(&p.dquote);
		delete_int(&p.squote);
		init_parsing_list_c(&p);
		delete_parsing_list_c(&p);
		check_quote_3(&p);
		//check_for_envvar(&p);
		printf("--------fin quote 3--------\n");
		// essai envvar avant ou apres
		//create_parsing_dico(&p);
		cpd1(&p);
		//p.cmd_d = reverse_dico(&p.cmd_d);
		//printf(RED);
		//printf("dico p.cmd_d\n");
		//printll_dico(p.cmd_d);
		//printf(ENDC);
		//init_parsing_list(&p);
		// modif vv
		if (p.cmd_d)
		{
			create_path_access(&p);
			//p.struct_cmd.cmd = reverse(&p.struct_cmd.cmd);
			printf("\n les chemins = ");
			printll(p.struct_cmd.cmd);
		}
		//printf(GREEN);
		//printll(p.word);
		//printf(ENDC);
		//init_exe(&p);
		piping_main(&p);
		//printf(GREEN);
		//printll(p.word);
		//printf(ENDC);
		clean_memory_parsing(&p);
		printf("\na la fin du programme\n");
	}
	//printf(RED"----------------- sortie prgm ----------------\n"ENDC);
	clean_memory_end(&p);
	return (0);
}