/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:36:55 by jsollett          #+#    #+#             */
/*   Updated: 2022/12/21 10:47:11 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_dico	*getword_2(t_list **raw, char *search)
{
	int 	i;
	int		pos;
	char	*str;
	char	*c_tmp;
	t_dico	*word;

	i = 0;
	search = delimitateur(raw);
	pos = getpos_c(*raw, search);
	if (pos == -1)
		pos = size_stack(*raw);
	str = malloc((pos + 1) * sizeof(char));
	word = malloc(sizeof(t_dico));
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
	word->next = NULL;
	word->value = str;
	word->key = ft_strdup(search);
	return (word);
}

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

void	inclusion(t_list_i **sq, t_list_i **dq, int s_index, int d_index)
{// essai, pour trouver la plage entre ' ' et entre " " a tster
	if ((s_index <= (int)size_stack_int(*sq) / 2) && (d_index <= (int)size_stack_int(*dq) / 2))
	{
		if (getitem_int(*sq, 2*(s_index-1)) < (getitem_int(*dq, 2*(d_index-1))))
		{
			if (getitem_int(*sq, 2*(s_index-1) + 1) > (getitem_int(*dq, 2*(d_index-1) +1)))
				printf("type 1: \' \" \" \'\n");
		}
/* 		else
			printf("type 2: \" \' \" \'\n"); */
		else
		if (getitem_int(*dq, 2*(d_index-1)) < (getitem_int(*sq, 2*(s_index - 1))))
			{
				if (getitem_int(*dq, 2 * (d_index - 1) + 1) > (getitem_int(*sq, 2 * (s_index - 1) + 1)))
					printf("type 3: \" \' \' \"\n");
			}
	}
}
