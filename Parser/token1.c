/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:34:55 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/06 15:40:06 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_code_c(t_parser *p, char c)
{
	if (getpos_c(p->util.delim, &c) == -1)
		return (0);
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	if (c == '>')
		return (3);
	if (c == '<')
		return (4);
	if (c == '|')
		return (5);
	if (c == ' ')
		return (32);
	if (c == '$')
		return (36);
	return (0);
}

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

void	expand_to_value(t_parser *p)
{
	char	*tmp;
	t_dico	*env;
	int		i;

	p->util.key_l = reverse(&p->util.key_l);
	env = NULL;
	tmp = getall(&p->util.key_l);
	i = 0;
	if (get_key(p->envvar, tmp ) != -1)
	{
		env = getitem_dico(p->envvar, get_key(p->envvar, tmp));
		free(tmp);
		tmp = ft_strdup(env->value);
		while (i++ < (int)ft_strlen(tmp))
		{
			push_int(&p->util.code, p->util.code_nb);//2 ou 0 faux depend d'ou appele
		}
		create_raw_list(&p->util.raw_tmp, tmp);
		free (tmp);
	}
	else
	{
		delete(&p->util.key_l);
		free (tmp);
	}
}

// a verifier ????
void	get_inside_dquote2(t_parser *p)
{
	char	c;

	remove_pos_c(&p->util.raw, 0);
	c = *getitem_c(p->util.raw, 0);
	while (ft_strncmp(getitem_c(p->util.raw, 0), "\"", 1) != 0)
	{
		if (ft_strncmp(getitem_c(p->util.raw, 0), "$", 1) == 0)
		{
			// mettre cas $?
			remove_pos_c(&p->util.raw, 0);
			while (ft_isalnum(getitem_c(p->util.raw, 0)[0]))
			{
				transfer_c(&p->util.raw, &p->util.key_l);
			}
			p->util.code_nb = 2;
			expand_to_value(p);
			continue ;
		}
		transfer_c(&p->util.raw, &p->util.raw_tmp);
		push_int(&p->util.code, 2);
	}
	remove_pos_c(&p->util.raw, 0);
}
