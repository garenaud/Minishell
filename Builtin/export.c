/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:22:20 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/24 14:37:43 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parsing_export(t_parser *p)
{
	p->built.arg = reverse(&p->built.arg);
	while (size_stack(p->built.arg)
		&& ft_strncmp(getitem_c(p->built.arg, 0), "=", 1))
		transfer_c(&p->built.arg, &p->built.key_l);
	remove_pos_c(&p->built.arg, 0);
	while (size_stack(p->built.arg))
		transfer_c(&p->built.arg, &p->built.value_l);
	p->built.key_l = reverse(&p->built.key_l);
	p->built.value_l = reverse(&p->built.value_l);
	p->built.key = getall(&p->built.key_l);
	p->built.value = getall(&p->built.value_l);
}

static void	print_env(t_dico *dico)
{
	while (dico)
	{
		printf("declare -x %s=\"%s\"\n", (dico->key), (dico->value));
		dico = dico->next;
	}
}

void	tri_export(t_parser *p)
{
	int		max_pos;
	t_dico	*tmp;

	tmp = NULL;
	while (size_stack_dico(p->envvar))
	{
		max_pos = find_max_key(p->envvar);
		tmp = getitem_dico(p->envvar, max_pos);
		transfer_dico(&tmp, &p->built.tmp);
		remove_pos_dico(&p->envvar, max_pos);
	}
	p->envvar = reverse_dico(&p->built.tmp);
	p->envvar = reverse_dico(&p->envvar);
	print_env(p->envvar);
}

int	bultin_export(t_exe *curr, t_parser *p)
{
	p->built.i = 1;
	if (curr->cmd_tab[p->built.i] == NULL)
		tri_export(p);
	else
	{
		while (curr->cmd_tab[p->built.i])
		{
			create_raw_list(&p->built.arg, curr->cmd_tab[p->built.i]);
			parsing_export(p);
			if (get_key(p->envvar, p->built.key) == -1)
				push_dico(&p->envvar, p->built.key, p->built.value);
			else
			{
				remove_pos_dico(&p->envvar, get_key(p->envvar, p->built.key));
				push_dico(&p->envvar, p->built.key, p->built.value);
			}
			free(p->built.key);
			free(p->built.value);
			p->built.i++;
		}
	}
	p->return_val = 0;
	return (0);
}
