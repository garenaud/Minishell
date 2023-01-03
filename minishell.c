/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/03 21:23:48 by grenaud-         ###   ########.fr       */
=======
/*   Updated: 2022/12/29 10:38:29 by jsollett         ###   ########.fr       */
>>>>>>> jsollet
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
	init_pgrm(&p, env);// ne pas le deplacer
	get_path(&p, env);
	while ((p.line =readline("mini-->")))
	{
		//init_pgrm(&p, env);
		//printll(p.struct_path.split_path);
		init_pgrm(&p, env);
		get_path(&p, env);
		if (readline_manager(&p) == 1)
			break ;
<<<<<<< HEAD
=======
	//	printll(p.struct_path.split_path);
		/* init_pgrm(&p, env);
		get_path(&p, env); */
>>>>>>> jsollet
		create_raw_list(&p.raw, p.line);
		p.raw = reverse(&p.raw);

		init_parsing_list_c(&p);
		delete_parsing_list_c(&p);
		create_dico_list(&p.envvar, env);
		trim_list(&p.raw);
		check_for_envvar(&p);
<<<<<<< HEAD
		//printf("--------fin envvar--------\n");				
=======
		printf("--------fin envvar--------\n");
>>>>>>> jsollet
		delete_int(&p.dquote);
		delete_int(&p.squote);
		init_parsing_list_c(&p);
		delete_parsing_list_c(&p);
		check_quote_3(&p);
<<<<<<< HEAD
		//printf("--------fin quote 3--------\n");
=======
    //    check_for_envvar(&p);
		printf("--------fin quote 3--------\n");
>>>>>>> jsollet
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
			p.struct_cmd.cmd = reverse(&p.struct_cmd.cmd);
			printf("\n les chemins = ");
			printll(p.struct_cmd.cmd);
		}
<<<<<<< HEAD
		//printf(GREEN);
		//printll(p.word);
		//printf(ENDC);
		piping_main(&p);
		//init_exe(&p);
		//init_pipe_cmd(&p);
		//printll_exe(p.cmd_exe);
		//delete_exeline(&p.cmd_exe);
=======
		printf(GREEN);
		printll(p.word);
		printf(ENDC);
>>>>>>> jsollet
		clean_memory_parsing(&p);
	}
	printf(RED"----------------- sortie prgm ----------------\n"ENDC);
	clean_memory_end(&p);
	return (0);
}