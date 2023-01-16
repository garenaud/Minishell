/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/16 17:25:27 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_parser	p;

	(void)argc;
	(void)argv;
	p.line = NULL;
	p.envvar = NULL;//
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
//	rl_catch_signals = 0;
	init_pgrm(&p, env);
		create_dico_list(&p.envvar, env);// ***
	create_delim(&p);
	while ((p.line =readline("mini-->")))
	{
		init_pgrm(&p, env);
		get_path(&p, env);
		if (readline_manager(&p) == 1)
			break ;
		create_raw_list(&p.raw, p.line);
		printll_dico(p.envvar);
	//	p.raw = reverse(&p.raw);
//		create_dico_list(&p.envvar, env); // recree le dico pas une bonne idee
		{// test swap
			printf(PURP);
			printll_dico(p.envvar);
			//swap_dico(&p.envvar, 2, 1);
			printf(RED);
			find_min_key(p.envvar);
		//	find_max_key(p.envvar);
			printf(ENDC);
		}
//		create_delim(&p);
		tester(&p);
	//	trim_list(&p.raw);
	//	check_for_envvar(&p);
	//	delete_int(&p.dquote);// utile ?
	//	delete_int(&p.squote);//
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
	//	duplicate(p.cmd_d, p.cmd_copy);
		duplicate_1(&p.cmd_d, &p.cmd_copy);
		if (p.cmd_d)
		{
			create_path_access(&p);
			//printll(p.struct_cmd.cmd);
		}
		printf(GREEN);
		printll(p.word);
		printf(ENDC);
	//	piping_main(&p);
		init_exe(&p);
		bultin_search(&p, p.cmd_exe);
		clean_memory_parsing(&p);
	}
	clean_memory_end(&p);
	return (0);
}
