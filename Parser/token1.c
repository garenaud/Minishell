/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:34:55 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/24 10:06:11 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	code1(t_parser *p, char *c)
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

void	expand_interrogation(t_parser *p, char *tmp)
{
	int		i;
	char	*val;

	i = 0;
	val = ft_itoa(p->return_val);
	printf("\n val = %s \n", val);
	create_raw_list(&p->util.raw_tmp, val);
	while (i++ < (int)ft_strlen(val))
		push_int(&p->util.code, p->util.code_nb);
	free(val);
	free(tmp);
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
		expand_interrogation(p, tmp);
	else if (get_key(p->envvar, tmp) != -1)
	{
		env = getitem_dico(p->envvar, get_key(p->envvar, tmp));
		free(tmp);
		tmp = ft_strdup(env->value);
		delete_dico(&env);
		while (i++ < (int)ft_strlen(tmp))
			push_int(&p->util.code, p->util.code_nb);
		create_raw_list_and_free(&p->util.raw_tmp, tmp);
	}
	else
	{
		delete(&p->util.key_l);
		free (tmp);
	}
}
