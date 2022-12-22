/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:04 by jsollett          #+#    #+#             */
/*   Updated: 2022/12/21 13:28:57 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pgrm(t_parser *p, char *env[])
{
	p->env = env;
	//p->line = NULL;
	p->tmp = NULL;
	init_pgrm_list_c(p);
	init_pgrm_file(p);
	init_pgrm_cmd(p);
	init_pgrm_dico(p);
	init_pgrm_list_i(p);
	init_util(p);
	init_struct_path(p);
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

void	add_space(t_parser *p)
{
	t_list	*tmp;

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
