/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleaning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:45:58 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/26 16:43:44 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_memory_end(t_parser *p)
{
	delete(&p->struct_path.split_path);
	delete(&p->struct_path.path_raw);
	if (p->line)
		free(p->struct_path.path);
	delete(&p->struct_cmd.cmd);
	delete_dico(&p->cmd_d);
	free(p->cmd_d);
	free(p->signal);
	delete_int(&p->flag);
	delete(&p->util.delim);
	delete_dico(&p->envvar);
	if (p->line)
		free(&p->struct_path.path);
}

void	clean_memory_parsing(t_parser *p)
{
	delete(&p->word);
	delete(&p->raw);
	delete_int(&p->dquote);
	delete_int(&p->squote);
	free(p->line);
	delete_dico(&p->check);
	delete(&p->struct_path.split_path);
	delete(&p->struct_path.path_raw);
	delete(&p->struct_cmd.cmd);
	delete_dico(&p->cmd_d);
	delete_dico(&p->cmd_copy);
	free(p->cmd_d);
	delete_int(&p->flag);
	delete_parsing_list_c(p);
	delete(&p->struct_cmd.cmd);
	delete_exeline(&p->cmd_exe);
}
