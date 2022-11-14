/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/14 16:30:28 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
 	t_list		*path_raw;
	t_list		*split_path;
	t_list		*env_list;
	char		*path;
	char		*tmp;
	
	// test dico
	t_dico		*dico;
	t_dico		*dico_tmp;
	
	dico = NULL;
	dico_tmp = NULL;
 /* 	push_dico(&dico, "key 1", "value 1");
	push_dico(&dico, "key 2", "value 2");
	push_dico(&dico, "key 3", "value 3");
	push_dico(&dico, "key 4", "value 4"); */
	//delete_dico(&dico);
	/* dico = reverse_dico(&dico);
	dico_tmp = getitem_dico(dico,2); */
	create_dico_list(&dico, env);
	printll_dico(&dico);
	delete_dico(&dico);
	// 
	path_raw = NULL;
	split_path = NULL;
 	env_list = NULL;
	create_env_list(&env_list, env);
	
	
	delete(&env_list);
	
	path = path_list(env);
	printf("path list = %s\n", path);
	create_raw_list(&path_raw, path);
	path_raw = reverse(&path_raw);

	while (size_stack(path_raw ))
	{
		trim_list(&path_raw);
		tmp = getpath(&path_raw);
		if (ft_strncmp(tmp,"", 1))
		{
			push(&split_path, tmp);
			free(tmp);
		}
		else
			free(tmp);
	}
	split_path = reverse(&split_path);
	printll(split_path);
	delete(&split_path);	 
	delete(&path_raw);
	
	t_parser	p;

	
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
		init_pgrm(&p, env);
		p.env = env; 
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

	create_quote_list(&p.raw, &p.dquote, "\"");
	create_quote_list(&p.raw, &p.squote, "\'");
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
	printll(p.word);
	delete(&p.word);
	delete(&p.raw);
	delete_int(&p.dquote);
	delete_int(&p.squote);
	free(p.line);
	}
	return (0);
}
