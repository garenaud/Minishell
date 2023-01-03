/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:18:38 by jsollett          #+#    #+#             */
/*   Updated: 2022/12/27 11:01:03 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_struct_path(t_parser *p)
{
	p->struct_path.path = NULL;
	p->struct_path.path_raw = NULL;
	p->struct_path.split_path = NULL;
	p->struct_path.env_list = NULL;
}

void	init_util(t_parser *p)
{
	p->util.flag = 0;
	p->util.position = 0;
	p->util.i1 = 0;
	p->util.i2 = 0;
	p->util.c_tmp = NULL;
	p->util.c_tmp1 = NULL;
	p->util.key = NULL;
	p->util.tmp = NULL;
}

void	init_parsing_list(t_parser *p)
{
	create_quote_list(&p->word, &p->pipe_i, "|");
	create_quote_list(&p->word, &p->to_out_i, ">");
	create_quote_list(&p->word, &p->to_in_i, "<");
	create_quote_list(&p->word, &p->append_i, ">>");
	create_quote_list(&p->word, &p->heredoc_i, "<<");
	create_quote_list(&p->raw, &p->dquote, "\"");
	create_quote_list(&p->raw, &p->squote, "\'");
//	create_quote_list(&p->raw, &p->dollars, "$");
}

void	init_parsing_list_c(t_parser *p)
{
	create_quote_list(&p->raw, &p->pipe_i, "|");
	create_quote_list(&p->raw, &p->to_out_i, ">");
	create_quote_list(&p->raw, &p->to_in_i, "<");
	//create_quote_list(&p->raw, &p->append_i, ">>");
	//create_quote_list(&p->raw, &p->heredoc_i, "<<");
	create_quote_list(&p->raw, &p->dquote, "\"");
	create_quote_list(&p->raw, &p->squote, "\'");
}
