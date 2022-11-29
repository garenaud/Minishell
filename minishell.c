/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/29 11:50:01 by jsollett         ###   ########.fr       */
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
		trim_list(&p.raw);// sinon segfault
        check_quote_3(&p);
        //
  /*       t_dico  *test;
        int i1 = 0;
        int i2 = 0;
        char    *w_tmp;
        char    *key;
        t_list  *ext;
        test = NULL;
        ext = NULL; */
        //
        //
/*         while (size_stack(p.raw) && size_stack_int(p.flag))
        {
            i1 = pop_int(&p.flag);
            w_tmp = pop(&p.raw);
            push(&ext, w_tmp);
            free(w_tmp);
            while (size_stack(p.raw) && size_stack_int(p.flag))
            {// a mettre condition pour separer suivant space
                i2 = getitem_int(p.flag, 0);
                pop_int(&p.flag);
                w_tmp = pop(&p.raw);
                push(&ext, w_tmp);
                if ((i2 != i1) || (i1 == 0 && ft_strncmp(w_tmp, " ", 1) == 0) || size_stack(p.raw) == 0)
                {
                    if (i1 == 0)
                        key = "0";
                    if (i1 == 1)
                        key = "1";
                    if (i1 == 2)
                        key = "2";
                    
                    if (size_stack(p.raw))
                    {// debug ok
                        free(w_tmp);
                        w_tmp = pop(&ext);
                        push(&p.raw,w_tmp);// leak
                        push_int(&p.flag, i2);// leak
                        free(w_tmp);
                    }
                    else
                        free(w_tmp);
                    ext = reverse(&ext);
                   // free(w_tmp);//
                    w_tmp = getall(&ext);
                    delete(&ext);
                    push_dico(&test, key, w_tmp);
                    free(w_tmp);
                    break ;
                }
                free(w_tmp); 
            }
        }
        test = reverse_dico(&test);
        printf(RED);
        printll_dico(test);
        printf(ENDC);
        delete_dico(&test); */
        
        create_parsing_dico(&p);
        
       /*  
        //
        //check_quote_1(&p); // leak
		// traitement de la raw_list
		while (size_stack(p.raw ))
		{
			trim_list(&p.raw);
			p.cmd_d_tmp = getword_2(&p.raw, " ");//
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
 */
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
