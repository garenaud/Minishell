/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:04 by jsollett          #+#    #+#             */
/*   Updated: 2022/11/08 14:13:24 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pgrm(t_parser *p, char *env[])
{
	p->raw = NULL;
    p->word = NULL;
    p->dquote = NULL;
    p->squote = NULL;
 //   p->line = NULL;
	p->env = env;
}

void    free_parsing(t_parser *p)
{
    delete(&p->word);
	delete(&p->raw);
	delete_int(&p->dquote);
	delete_int(&p->squote);
	free(p->line);
//    free(p->tmp);
    free(p->raw);
    free(p->word);
}