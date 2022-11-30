/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/30 10:23:36 by jsollett         ###   ########.fr       */
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
	init_pgrm(&p, env);	// ne pas le deplacer
	while ((p.line =readline("mini-->")))
	{
		init_pgrm(&p, env);	
		get_path(&p, env);
        if (readline_manager(&p) == 1)
			break ;
		/* init_pgrm(&p, env);	
		get_path(&p, env); */
		create_raw_list(&p.raw, p.line);
		p.raw = reverse(&p.raw);
    	init_parsing_list_c(&p);
		delete_parsing_list_c(&p);
        create_dico_list(&p.envvar, env);//
		trim_list(&p.raw);// sinon segfault
        check_quote_3(&p);
        //
        
        create_parsing_dico(&p);
        

/* 		p.cmd_d = reverse_dico(&p.cmd_d);
	 	printf(RED);
	 	printf("dico p.cmd_d\n");
	 	printll_dico(p.cmd_d);
	 	printf(ENDC); */
 
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
        // 
        delete_int(&p.flag);
        delete_dico(&p.envvar);
	}
	printf(RED"----------------- sortie prgm ----------------\n"ENDC);
	delete(&p.struct_path.split_path);	 
	delete(&p.struct_path.path_raw);
	delete(&p.struct_cmd.cmd);
	delete_dico(&p.cmd_d);
	free(p.cmd_d);
    //
    delete_int(&p.flag);
	return (0);
}
