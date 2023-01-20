/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:34:55 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/19 13:40:59 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_code_c1(t_parser *p, char *c)
{
	if (getpos_c(p->util.delim, c) == -1)
		return (0);
	if (ft_strncmp(c, "\'", 1) == 0)
		return (1);
	if (ft_strncmp(c, "\"", 1) == 0)
		return (2);
	if (ft_strncmp(c, ">", 1) == 0)
		return (3);
	if (ft_strncmp(c, "<", 1) == 0)
		return (4);
	if (ft_strncmp(c, "|", 1) == 0)
		return (5);
	if (ft_strncmp(c, " ", 1) == 0)
		return (32);
	if (ft_strncmp(c, "$", 1) == 0)
		return (36);
	if (ft_strncmp(c, "=", 1) == 0)
		return (61);
	return (0);
}

int	get_code_s(char *s)
{
	if (ft_strncmp(s, "<<", 2) == 0)
		return (6);
	if (ft_strncmp(s, ">>", 2) == 0)
		return (7);
	if (ft_strncmp(s, "||", 2) == 0)
		return (8);
	return (-1);
}

// a tester
void	transfer_2c_space(t_parser *p, char *s)
{
	int	code;

	code = get_code_s(s);
	if (code >= 6 && code <= 8)
	{
		push_int(&p->util.code, 32);
		push(&p->util.raw_tmp, " ");
		push_int(&p->util.code, code);
		transfer_c(&p->util.raw, &p->util.raw_tmp);
		push_int(&p->util.code, code);
		transfer_c(&p->util.raw, &p->util.raw_tmp);
		push_int(&p->util.code, 32);
		push(&p->util.raw_tmp, " ");
	}
}

void	expand_interrogation(t_parser *p)
{
	int	i;

	i = 0;
	create_raw_list(&p->util.raw_tmp, ft_itoa(p->return_val));
	while (i++ < (int)ft_strlen(ft_itoa(p->return_val)))
		push_int(&p->util.code, p->util.code_nb);
}

void	expand_to_value(t_parser *p)
{
	char	*tmp;
	t_dico	*env;
	int		i;

	p->util.key_l = reverse(&p->util.key_l);
	env = NULL;
	tmp = getall(&p->util.key_l);
	i = 0;
	if (ft_strncmp(tmp, "?", 1) == 0)
		expand_interrogation(p);
	else if (get_key(p->envvar, tmp) != -1)
	{
		env = getitem_dico(p->envvar, get_key(p->envvar, tmp));
		free(tmp);
		tmp = ft_strdup(env->value);
		while (i++ < (int)ft_strlen(tmp))
			push_int(&p->util.code, p->util.code_nb);//2 ou 0 faux depend d'ou appele
		create_raw_list(&p->util.raw_tmp, tmp);
		free (tmp);
	}
	else
	{
		delete(&p->util.key_l);
		free (tmp);
	}
}

