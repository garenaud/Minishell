/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:04 by jsollett          #+#    #+#             */
/*   Updated: 2022/11/21 12:13:22 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pgrm(t_parser *p, char *env[])
{
	p->raw = NULL;
    p->word = NULL;
    p->dquote = NULL;
    p->squote = NULL;
    p->pipe_i = NULL;
    p->to_out_i = NULL;
    p->to_in_i = NULL;
    p->append_i = NULL;
    p->heredoc_i = NULL;
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
    p->check = NULL;
    p->tmp = NULL;
    p->struct_file.file = NULL;
    p->struct_file.fd = NULL;
    p->struct_file.rwx = NULL;
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

void    init_parsing_list(t_parser *p)
{
    create_quote_list(&p->word, &p->pipe_i, "|");
    create_quote_list(&p->word, &p->to_out_i, ">");
    create_quote_list(&p->word, &p->to_in_i, "<");
    create_quote_list(&p->word, &p->append_i, ">>");
    create_quote_list(&p->word, &p->heredoc_i, "<<");
    create_quote_list(&p->raw, &p->dquote, "\"");
	create_quote_list(&p->raw, &p->squote, "\'");
}

void    init_parsing_list_c(t_parser *p)
{
    create_quote_list(&p->raw, &p->pipe_i, "|");
    create_quote_list(&p->raw, &p->to_out_i, ">");
    create_quote_list(&p->raw, &p->to_in_i, "<");
    //create_quote_list(&p->raw, &p->append_i, ">>");
    //create_quote_list(&p->raw, &p->heredoc_i, "<<");
    create_quote_list(&p->raw, &p->dquote, "\"");
	create_quote_list(&p->raw, &p->squote, "\'");
}

void    delete_parsing_list_c(t_parser *p)
{
    delete_int(&p->pipe_i);
    delete_int(&p->to_out_i);
    delete_int(&p->to_in_i);
}

void    add_space(t_parser *p)
{
    t_list *tmp;
  
    tmp = NULL;
    while (size_stack(p->raw))
    {
        if ((ft_strncmp(getitem(p->raw, 0), "|", 1) == 0) 
            && ft_strncmp(getitem(p->raw, 1), "|", 1) == 0)
        {
            push(&tmp, " ");
            transfer_c(&p->raw, &tmp);
            transfer_c(&p->raw, &tmp);
            push(&tmp, " ");
        }
        else if ((ft_strncmp(getitem(p->raw, 0), "|", 1) == 0) 
            && ft_strncmp(getitem(p->raw, 1), "|", 1) != 0)
        {
            push(&tmp, " ");
            transfer_c(&p->raw, &tmp);
            push(&tmp, " ");
        }
        else
        {
            transfer_c(&p->raw, &tmp);
        }
    }
    while (size_stack(tmp))
    {
        transfer_c(&tmp, &p->raw);
    }
    printf(YEL);
    printll(p->raw);
    printf(ENDC);
}