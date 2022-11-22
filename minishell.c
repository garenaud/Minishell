/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/21 17:10:49 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	t_list		*test;
	t_list		*testw; 
// ajout
	t_dico		*word;
	t_dico		*word_tmp;
	word_tmp = NULL;
	word = NULL;
	
	testw = NULL;
	test = NULL;

	char		*tmp1;
	
	t_parser	p;
	tmp1 = NULL;

	init_pgrm(&p, env);	
	get_path(&p, env);


	(void)argc;
	(void)argv;
	p.line = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	rl_catch_signals = 0;
	
	while ((p.line =readline("mini-->")))
	{
		signal(SIGINT, sig_handler);
// 		init_pgrm(&p, env);
		if (strcmp(p.line,"quit") == 0)
		{
			free_parsing(&p);
			break ;
		}
		if (strcmp(p.line,"") == 0)
		{
        	rl_on_new_line();// recree le prompt sur la nvlle ligne
        	rl_replace_line("", 0);// efface l'ancien contenu
      		rl_redisplay();// et affiche
		}
		if (strcmp(p.line,"clear") == 0)
			rl_clear_history();
		if (strlen(p.line) > 0)
			add_history(p.line);
	
		create_raw_list(&p.raw, p.line);
		p.raw = reverse(&p.raw);
		init_parsing_list_c(&p);//****************
		//check_quote_1(&p); // leak
		printf(GREEN);
		printll(p.raw);
		//add_space(&p);//***************
		printll(p.raw);
		printf(ENDC);
		delete_parsing_list_c(&p);
		trim_list(&p.raw);// sinon segfault
		while (size_stack(p.raw ))
		{
			trim_list(&p.raw);
			word_tmp = getword_2(&p.raw, " ");
			if (ft_strncmp(word_tmp->value,"", 1))
			{
				push_dico(&word,word_tmp->key, word_tmp->value);
				delete_dico(&word_tmp);
				free(word_tmp);
			}
			else
			{
				printf("tmp vide= [%s]\n", word_tmp->value);
				delete_dico(&word_tmp);
				free(word_tmp);
			}
			free(word_tmp);
		}

		word = reverse_dico(&word);
		printf(RED);
		printf("dico word\n");
		printll_dico(word);
		printf(ENDC);

		//init_parsing_list(&p);

	 	if (p.word)
		{
			create_path_access(test, &p);
			printll(p.struct_cmd.cmd);
		}
		printf(GREEN);
		printll(p.word);
		printf(ENDC);
		delete(&test);//
	
		delete(&testw);
		free(tmp1);
		delete(&p.word);
		delete(&p.raw);
		delete_int(&p.dquote);
		delete_int(&p.squote);
		free(p.line);
		delete_dico(&p.check);
		delete(&p.struct_path.split_path);	 
		delete(&p.struct_path.path_raw);
		delete(&p.struct_cmd.cmd);
		delete_dico(&word);
		free(word);
	}
	printf(RED"----------------- sortie prgm ----------------\n"ENDC);
	delete(&p.struct_path.split_path);	 
	delete(&p.struct_path.path_raw);
	delete(&p.struct_cmd.cmd);
	delete_dico(&word);
	free(word);
	return (0);
}
