/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:04 by jsollett          #+#    #+#             */
/*   Updated: 2022/11/16 16:00:04 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pgrm(t_parser *p, char *env[])
{
	p->raw = NULL;
    p->word = NULL;
    p->dquote = NULL;
    p->squote = NULL;
    p->struct_path.path = NULL;
    p->struct_path.path_raw = NULL;
    p->struct_path.split_path = NULL;
    p->struct_path.env_list = NULL;
    p->dico = NULL;
    p->dico_tmp = NULL;
	p->env = env;
    p->struct_cmd.cmd = NULL;
    p->struct_cmd.option = NULL;
    p->struct_cmd.arg = NULL;
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