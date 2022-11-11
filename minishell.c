/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/11 13:11:09 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	/* t_list		*raw = NULL;
	t_list		*word = NULL;
	t_list_i	*dquote = NULL;
	t_list_i	*squote = NULL;
	char   		*line = NULL;
	char	**env_1; */

//	test partie path	
/* 	t_list		*path_raw;
	char		*path;
	char		*tmp;
	
	path = getenv("PATH");
	create_raw_list(&path_raw, path);
	path_raw = reverse(&path_raw);
	printll(path_raw);
	while (size_stack(path_raw ))
	{
		trim_list(&path_raw);
		tmp = getpath(&path_raw);//<<
		if (ft_strncmp(tmp,"", 1))
		{
			push(&p.word,p.tmp);
			free(p.tmp);	//
		}
		else
		{
			printf("tmp vide= [%s]\n", p.tmp);
			free(p.tmp);
		}
	}
		 */
	//char	*tmp;
	t_parser	p;
	// test getenv
  printf("PATH : %s\n", getenv("PATH"));
   printf("HOME : %s\n", getenv("HOME"));
   printf("ROOT : %s\n", getenv("ROOT"));
	
	(void)argc;
	(void)argv;
//	init_pgrm(&p, env);
	p.line = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	rl_catch_signals = 0;
	while ((p.line =readline("mini-->")))
	{
//	signal(SIGINT, sig_handler);
		init_pgrm(&p, env);
		p.env = env; 
		if (strcmp(p.line,"quit") == 0)
		{
			free_parsing(&p);
			printf("OUT\n");
			//free(p.line); //aussi delete all...
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
		{
			add_history(p.line);
		}
	
	create_raw_list(&p.raw, p.line);
	p.raw = reverse(&p.raw);// leak
	trim_list(&p.raw);

	create_quote_list(&p.raw, &p.dquote, "\"");
	create_quote_list(&p.raw, &p.squote, "\'");
	while (size_stack(p.raw ))
	{
		trim_list(&p.raw);
		p.tmp = getword1(&p.raw, " ");// leak
		if (ft_strncmp(p.tmp,"", 1))
		{
			push(&p.word,p.tmp);
			free(p.tmp);	//
		}
		else
		{
			printf("tmp vide= [%s]\n", p.tmp);
			free(p.tmp);
		}
	}
	p.word = reverse(&p.word);//leak
	printll(p.word);
	delete(&p.word);
	delete(&p.raw);
	delete_int(&p.dquote);
	delete_int(&p.squote);
	free(p.line);
		
	}
	return (0);
}
