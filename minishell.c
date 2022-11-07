/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/07 16:07:32 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	t_list		*raw = NULL;
	t_list		*word = NULL;
	t_list_i	*dquote = NULL;
	t_list_i	*squote = NULL;
	char   		*line = NULL;
	char	*tmp;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	rl_catch_signals = 0;
	while ((line =readline("mini-->")))
	{
//	signal(SIGINT, sig_handler);
		if (strcmp(line,"quit") == 0)
		{
			free(line);
			break ;
		}
		if (strcmp(line,"") == 0)
		{

        rl_on_new_line();// recree le prompt sur la nvlle ligne
        rl_replace_line("", 0);// efface l'ancien contenu
        rl_redisplay();// et affiche
		}
		if (strcmp(line,"clear") == 0)
			rl_clear_history();
		if (strlen(line) > 0)
		{
			add_history(line);
		}
	create_raw_list(&raw, line);
	raw = reverse(&raw);
	trim_list(&raw);

	create_quote_list(&raw, &dquote, "\"");
	create_quote_list(&raw, &squote, "\'");
	while (size_stack(raw ))
	{
		trim_list(&raw);
		tmp = getword1(&raw, " ");
		if (ft_strncmp(tmp,"", 1))
		{
			push(&word,tmp);	
		}
		else
			printf("tmp vide= [%s]\n", tmp);
	}
	word = reverse(&word);
	printll(word);
	delete(&word);
	delete(&raw);
	delete_int(&dquote);
	delete_int(&squote);
	free(line);					
	}
	return (0);
}
