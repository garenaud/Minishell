/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:26:45 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/16 10:32:28 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pgrm_list_i(t_parser *p)
{
	p->dquote = NULL;
	p->squote = NULL;
	p->pipe_i = NULL;
	p->to_out_i = NULL;
	p->to_in_i = NULL;
	p->append_i = NULL;
	p->heredoc_i = NULL;
	p->word_len = NULL;
	p->flag = NULL;
}

void	init_pgrm_list_c(t_parser *p)
{
	p->raw = NULL;
	p->word = NULL;
}

void	init_pgrm_dico(t_parser *p)
{
	p->check = NULL;
	p->cmd_d = NULL;
	p->cmd_d_tmp = NULL;
	p->dico = NULL;
	p->dico_tmp = NULL;
	p->cmd_copy = NULL;
//	p->envvar = NULL;
}

void	init_pgrm_file(t_parser *p)
{
	p->struct_file.file = NULL;
	p->struct_file.fd = NULL;
	p->struct_file.rwx = NULL;
}

void	init_pgrm_cmd(t_parser *p)
{
	p->struct_cmd.cmd = NULL;
	p->struct_cmd.option = NULL;
	p->struct_cmd.arg = NULL;
}
