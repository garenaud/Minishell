/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:56:10 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/26 16:34:26 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_alterned_redir(t_parser *p)
{
	int		index;
	t_dico	*tmp1;
	t_dico	*tmp;

	tmp = NULL;
	tmp1 = NULL;
	index = 1;
	while (index < (int) size_stack_dico(p->cmd_d))
	{
		tmp1 = getitem_dico(p->cmd_d, index);
		tmp = getitem_dico(p->cmd_d, index - 1);
		if (ft_strncmp(tmp->key, "3", 1) == 0
			&& ft_strncmp(tmp1->key, "4", 1) == 0)
			p->error = -32;
		if (ft_strncmp(tmp->key, "4", 1) == 0
			&& ft_strncmp(tmp1->key, "3", 1) == 0)
			p->error = -32;
		delete_dico(&tmp);
		delete_dico(&tmp1);
		index ++;
	}
}

void	check_redir_pipe(t_parser *p)
{
	int		index;
	t_dico	*tmp1;
	t_dico	*tmp;

	tmp = NULL;
	tmp1 = NULL;
	index = 1;
	while (index < (int) size_stack_dico(p->cmd_d))
	{
		tmp1 = getitem_dico(p->cmd_d, index);
		tmp = getitem_dico(p->cmd_d, index - 1);
		if ((ft_strncmp(tmp->key, "3", 1) == 0
				&& ft_strncmp(tmp1->key, "5", 1) == 0)
			|| (ft_strncmp(tmp->key, "4", 1) == 0
				&& ft_strncmp(tmp1->key, "5", 1) == 0))
			p->error = -32;
		if ((ft_strncmp(tmp->key, "6", 1) == 0
				&& ft_strncmp(tmp1->key, "5", 1) == 0)
			|| (ft_strncmp(tmp->key, "7", 1) == 0
				&& ft_strncmp(tmp1->key, "5", 1) == 0))
			p->error = -32;
		delete_dico(&tmp);
		delete_dico(&tmp1);
		index ++;
	}
}

int	print_syntax_err(t_parser *p, int err)
{
	if (err == -5)
	{
		printf ("Minishell: syntax error near unexpected token `|'\n");
		p->return_val = 258;
		return (-5);
	}
	if (err < -1)
	{
		printf ("Minishell: syntax error near unexpected token `< or >'\n");
		p->return_val = 258;
		return (-32);
	}
	return (-1);
}

int	check_pathos(t_parser *p)
{
	int		index;
	t_dico	*tmp1;
	t_dico	*tmp;

	tmp = NULL;
	tmp1 = NULL;
	index = 0;
	check_help(p);
	if (p->error < 0)
		return (print_syntax_err(p, p->error));
	check_succ_redir(p);
	if (p->error < 0)
		return (print_syntax_err(p, p->error));
	check_alterned_redir(p);
	if (p->error < 0)
		return (print_syntax_err(p, p->error));
	check_redir_pipe(p);
	if (p->error < 0)
		return (print_syntax_err(p, p->error));
	return (1);
}
