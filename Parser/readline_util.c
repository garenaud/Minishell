/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:37 by jsollett          #+#    #+#             */
/*   Updated: 2022/11/23 11:42:39 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    sig_handler(int signum)
{//https://stackoverflow.com/questions/16828378/readline-get-a-new-prompt-on-sigint
    if (signum == SIGINT)
    {// ordre important !!!
        printf("\n");// va vers une nvlle ligne
        rl_on_new_line();// recree le prompt sur la nvlle ligne
        rl_replace_line("", 0);// efface l'ancien contenu
        rl_redisplay();// et affiche
    }
	if (signum == SIGABRT)
		signal(SIGABRT, SIG_IGN); 
}

int readline_manager(t_parser *p)
{
    signal(SIGINT, sig_handler);
    if (strcmp(p->line,"quit") == 0)
		{
			free_parsing(p);
			return (1);
		}
		if (strcmp(p->line,"") == 0)
		{
        	rl_on_new_line();// recree le prompt sur la nvlle ligne
        	rl_replace_line("", 0);// efface l'ancien contenu
      		rl_redisplay();// et affiche
		}
		if (strcmp(p->line,"clear") == 0)
			rl_clear_history();
		if (strlen(p->line) > 0)
			add_history(p->line);
    return (0);
}