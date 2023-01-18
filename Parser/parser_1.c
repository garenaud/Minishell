/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:36:55 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/18 09:57:53 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getword1(t_list **raw, char *search)
{
	int		i;
	int		pos;
	char	*str;
	char	*c_tmp;

	i = 0;
	search = delimitateur(raw);
	pos = getpos_c(*raw, search);
	if (pos == -1)
		pos = size_stack(*raw);
	str = malloc((pos + 1) * sizeof(char));
	while (i < pos)
	{
		c_tmp = pop(raw);
		str[i] = *c_tmp;
		free(c_tmp);
		i++;
	}
	if (size_stack(*raw) != 0)
		remove_pos_c(raw, 0);
	str[i] = '\0';
	return (str);
}

char	*getall(t_list **raw)
{
	int		i;
	int		pos;
	char	*str;
	char	*c_tmp;

	i = 0;
	pos = size_stack(*raw);
	str = malloc((pos + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < pos)
	{
		c_tmp = pop(raw);
		str[i] = *c_tmp;
		free(c_tmp);
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	create_raw_list(t_list **str, char *line)
{
	int		i;
	char	tmp[2];

	i = 0;
	while (line[i] != '\0')
	{
		tmp[0] = line[i];
		tmp[1] = '\0';
		push(str, tmp);
		i++;
	}
}

void	create_quote_list(t_list **str, t_list_i **pos, char *search)
{
	int	i;
	int	len;

	len = ft_strlen(search);
	i = 0;
	while (i < (int)size_stack(*str))
	{
		if ((ft_strncmp(getitem(*str, i), search, len) == 0))
		{
			push_int(pos, i);
		}
		i++;
	}
	*pos = reverse_int(pos);
}

void	cpd1_key(t_parser *p)
{
	if (p->util.i1 == 0)
		p->util.key = "0";
	if (p->util.i1 == 1)
		p->util.key = "1";
	if (p->util.i1 == 2)
		p->util.key = "2";
	if (p->util.i1 == 3)
		p->util.key = "3";
	if (p->util.i1 == 4)
		p->util.key = "4";
	if (p->util.i1 == 5)
		p->util.key = "5";
	if (p->util.i1 == 6)
		p->util.key = "6";
	if (p->util.i1 == 7)
		p->util.key = "7";
	if (p->util.i1 == 8)
		p->util.key = "8";
}
