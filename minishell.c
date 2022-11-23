/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/23 17:08:20 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;	
	t_parser	p;


//	init_pgrm(&p, env);	
//	get_path(&p, env);
	p.line = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	rl_catch_signals = 0;
	
	while ((p.line =readline("mini-->")))
	{
		if (readline_manager(&p) == 1)
			break ;
		init_pgrm(&p, env);	
		get_path(&p, env);
		create_raw_list(&p.raw, p.line);
		p.raw = reverse(&p.raw);
		init_parsing_list_c(&p);//****************
		//check_quote_1(&p); // leak
		/* printf(GREEN);
		printll(p.raw);
		//add_space(&p);//
		printll(p.raw);
		printf(ENDC); */
		delete_parsing_list_c(&p);
		trim_list(&p.raw);// sinon segfault
		
		while (size_stack(p.raw ))
		{
			trim_list(&p.raw);
			p.cmd_d_tmp = getword_2(&p.raw, " ");
			if (ft_strncmp(p.cmd_d_tmp->value, "", 1))
			{
				push_dico(&p.cmd_d, p.cmd_d_tmp->key, p.cmd_d_tmp->value);
				delete_dico(&p.cmd_d_tmp);
				free(p.cmd_d_tmp);
			}
			else
			{
				printf("tmp vide= [%s]\n", p.cmd_d_tmp->value);
				delete_dico(&p.cmd_d_tmp);
				free(p.cmd_d_tmp);
			}
			free(p.cmd_d_tmp);
		}

		p.cmd_d = reverse_dico(&p.cmd_d);
	 	printf(RED);
	 	printf("dico p.cmd_d\n");
	 	printll_dico(p.cmd_d);
	 	printf(ENDC);
 
		//init_parsing_list(&p);
		// modif vv
	 	if (p.cmd_d)
		{
			create_path_access( &p);
			printll(p.struct_cmd.cmd);
		}
		/* printf(GREEN);
		printll(p.word);
		printf(ENDC); */
	
		delete(&p.word);
		delete(&p.raw);
		delete_int(&p.dquote);
		delete_int(&p.squote);
		free(p.line);
		delete_dico(&p.check);
		delete(&p.struct_path.split_path);	 
		delete(&p.struct_path.path_raw);
		delete(&p.struct_cmd.cmd);
		delete_dico(&p.cmd_d);
		free(p.cmd_d);
	}
	printf(RED"----------------- sortie prgm ----------------\n"ENDC);
	delete(&p.struct_path.split_path);	 
	delete(&p.struct_path.path_raw);
	delete(&p.struct_cmd.cmd);
	delete_dico(&p.cmd_d);
	free(p.cmd_d);
	return (0);
}
