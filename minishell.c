/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/17 16:11:57 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
/*  	t_list		*path_raw;
	t_list		*split_path;
	t_list		*env_list; */
	t_list		*test;
	t_list		*testw; 

	testw = NULL;
	test = NULL;
	char		*tmp;
	char		*tmp1;
	int			index;
	t_parser	p;
	tmp1 = NULL;
	// test dico
/* 	t_dico		*dico;
	t_dico		*dico_tmp;
	
	dico = NULL;
	dico_tmp = NULL; */
 
	init_pgrm(&p, env);
	create_dico_list(&p.dico, env);
	printll_dico(p.dico);
	index = get_key(p.dico, "CPPFLAGS");
	p.dico_tmp = getitem_dico(p.dico, index);
	printf("\n\n\n");
	printf("DICO TMP ***************\n");
	printll_dico(p.dico_tmp);
	
	delete_dico(&p.dico_tmp);
	//printf("notre dico tmp= %s %s", dico_tmp->key, dico_tmp->value);	
	printf("\n\n\n");
	printf("index = %d\n", index);
	remove_pos_dico(&p.dico, index);
	printf("\n\n\n");
	printf("%p\n", p.dico);
	printll_dico(p.dico); 
	
	
	delete_dico(&p.dico);
	// 
	/* path_raw = NULL;
	split_path = NULL;
 	env_list = NULL; */
	create_env_list(&p.struct_path.env_list, env);
	
	
	delete(&p.struct_path.env_list);
	
	p.struct_path.path = path_list(env);
	printf("\n\n path list = %s\n", p.struct_path.path);
	create_raw_list(&p.struct_path.path_raw, p.struct_path.path);
	p.struct_path.path_raw = reverse(&p.struct_path.path_raw);

	while (size_stack(p.struct_path.path_raw ))
	{
		trim_list(&p.struct_path.path_raw);
		tmp = getpath(&p.struct_path.path_raw);
		if (ft_strncmp(tmp,"", 1))
		{
			push(&p.struct_path.split_path, tmp);
			free(tmp);
		}
		else
			free(tmp);
	}
	p.struct_path.split_path = reverse(&p.struct_path.split_path);
	printll(p.struct_path.split_path);
//	delete(&split_path);	 
//	delete(&path_raw);
	

	
/* 	printf("PATH : %s\n", getenv("PATH"));lldb 
	printf("HOME : %s\n", getenv("HOME"));
	printf("ROOT : %s\n", getenv("ROOT")); */
	(void)argc;
	(void)argv;
	p.line = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	rl_catch_signals = 0;
	while ((p.line =readline("mini-->")))
	{
		signal(SIGINT, sig_handler);
/* 		init_pgrm(&p, env); */
		if (strcmp(p.line,"quit") == 0)
		{
			free_parsing(&p);
			printf("OUT\n");
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
		check_quote(&p);
		printf(GREEN);
		printll(p.raw);
		add_space(&p);//***************
		printll(p.raw);
		printf(ENDC);
		
		/* printf(RED"printll pipe\n"ENDC);
		printll_int(p.pipe_i);
		printf(RED"printll to_out\n"ENDC);
		printll_int(p.to_out_i);
		printf(RED"printll to_in\n"ENDC);
		printll_int(p.to_in_i);
		printf(RED"printll append\n"ENDC);
		printll_int(p.append_i);
		printf(RED"printll heredoc\n"ENDC);
		printll_int(p.heredoc_i); */
		/* create_quote_list(&p.raw, &p.dquote, "\"");
		create_quote_list(&p.raw, &p.squote, "\'"); */
		trim_list(&p.raw);// sinon segfault
		while (size_stack(p.raw ))
		{
			trim_list(&p.raw);
			p.tmp = getword1(&p.raw, " ");
			if (ft_strncmp(p.tmp,"", 1))
			{
				push(&p.word,p.tmp);
				free(p.tmp);
			}
			else
			{
				printf("tmp vide= [%s]\n", p.tmp);
				free(p.tmp);
			}
		}
		p.word = reverse(&p.word);
		init_parsing_list(&p);
		printf(RED"printll pipe\n"ENDC);
		printll_int(p.pipe_i);
		printf(RED"printll to_out\n"ENDC);
		printll_int(p.to_out_i);
		printf(RED"printll to_in\n"ENDC);
		printll_int(p.to_in_i);
		printf(RED"printll append\n"ENDC);
		printll_int(p.append_i);
		printf(RED"printll heredoc\n"ENDC);
		printll_int(p.heredoc_i);
		printf(RED);
		printll(p.word);
		printf(ENDC);
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
		//
		printll(p.word);
		delete(&p.word);
		delete(&p.raw);
		delete_int(&p.dquote);
		delete_int(&p.squote);
		free(p.line);
		delete_dico(&p.check);
	//	delete(&p.struct_path.split_path);	 
	//	delete(&p.struct_path.path_raw);
		delete(&p.struct_cmd.cmd);
	}
	printf(RED"----------------- sortie prgm ----------------\n"ENDC);
	delete(&p.struct_path.split_path);	 
	delete(&p.struct_path.path_raw);
	delete(&p.struct_cmd.cmd);
	return (0);
}
