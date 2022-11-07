/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:37 by jsollett          #+#    #+#             */
/*   Updated: 2022/11/07 14:02:32 by jsollett         ###   ########.fr       */
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