/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:04 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/18 17:02:23 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pgrm(t_parser *p, char *env[])
{
	p->env = env;
	p->tmp = NULL;
	init_pgrm_list_c(p);
	init_pgrm_file(p);
	init_pgrm_cmd(p);
	init_pgrm_dico(p);
	init_pgrm_list_i(p);
	init_util(p);
	init_struct_path(p);
	init_built(p);
}

void	init_built(t_parser *p)
{
	p->built.arg = NULL;
	p->built.key_l = NULL;
	p->built.value_l = NULL;
	p->built.tmp = NULL;
	//p->built.exception = 0;
}

void	free_parsing(t_parser *p)
{
	delete(&p->word);
	delete(&p->raw);
	delete_int(&p->dquote);
	delete_int(&p->squote);
	free(p->line);
	free(p->raw);
	free(p->word);
}

void	delete_parsing_list_c(t_parser *p)
{
	delete_int(&p->pipe_i);
	delete_int(&p->to_out_i);
	delete_int(&p->to_in_i);
}
