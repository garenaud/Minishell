/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:29:00 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/17 12:05:30 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getitem_c(t_list *top, size_t pos)
{
	if (pos >= size_stack(top))
		return (NULL);
	else
	{
		while (pos > 0)
		{
			top = top->next;
			pos--;
		}
		return (top->data);
	}
}

void	trim_list(t_list **str)
{
	while (size_stack(*str) && ft_strncmp(getitem_c(*str, 0)," ",1) == 0)
		remove_pos_c(str, 0);
	while (size_stack(*str) && ft_strncmp(getitem_c(*str, size_stack(*str) - 1)," ", 1) == 0)
		remove_pos_c(str, size_stack(*str) -1 );
}

/*
void	trim_list(t_list **str)
{
	int	count_s;
	int	count_e;

	count_s = 0;
	count_e = 0;
	while (ft_strncmp(getitem(*str, 0)," ",1) == 0)
		pop(str);
	while (ft_strncmp(getitem(*str, size_stack(*str) - 1)," ", 1) == 0)
		remove_position(str, size_stack(*str) -1 );
}
*/
/* char	*trim(char *line)
{
	int	i;
	int	j;
	int	count_s;
	int	count_e;
	char	*res;

	i = 0;
	j = 0;
	count_s = 0;
	count_e = 0;
	while (line[i] == ' ')
	{
		count_s++;
		if (line[i + 1] != ' ')
			break;
		i++;
	}
	i = ft_strlen(line);
	while (line[i] == ' ')
	{
		count_e++;
		if (line[i - 1] != ' ')
			break;
		i--;
	}
	res = malloc((ft_strlen(line) - count_s - count_e +1) * sizeof(char));
	if (res == NULL)
		exit(0);
	i = count_s;
	while (i < (int)ft_strlen(line) - count_e - count_s)
	{
		res[j] = line[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}
 */

/* char	*getword(t_list **raw, char *search)
{
	int i;
	int	pos;
	char	*str;

	i = 0;
	pos = getposition(*raw, search);
	if (pos == -1)
		pos = size_stack(*raw);
	str = malloc((pos +1)* sizeof(char));
	while (i < pos)
	{
		str[i] = *pop(raw);
		i++;
	}
	str[i] = '\0';
	return (str);
} */

char	*delimitateur(t_list **raw)
{//modifiee
	if (ft_strncmp(getitem(*raw, 0),"\"",1) == 0)
	{
		remove_pos_c(raw, 0);
		return ("\"");
	}
	else 
	if (ft_strncmp(getitem(*raw, 0),"\'",1) == 0)
	{
		remove_pos_c(raw, 0);
		return ("\'");
	}// ajout pour le path faux
/* 	if (ft_strncmp(getitem(*raw, 0),":",1) == 0)
	{
		remove_pos_c(raw, 0);
		return (":");
	} */
	else
	{
		return (" ");
	}
}



char	*getpath(t_list **raw)
{ // a tester
	int 	i;
	int		pos;
	char	*str;
	char	*c_tmp;

	i = 0;
	pos = getpos_c(*raw, ":");
	if (pos == -1)
		pos = size_stack(*raw);
	str = malloc((pos +1)* sizeof(char));
	while (i < pos)
	{
		c_tmp = pop(raw);
		str[i] = *c_tmp;
		free(c_tmp);
		i++;
	}
	if (size_stack(*raw) !=  0)
		remove_pos_c(raw,0);
	str[i] = '\0';
	return (str);
}

char	*getword1(t_list **raw, char *search)
{ //modifiee
	int 	i;
	int		pos;
	char	*str;
	char	*c_tmp;

	i = 0;	
	search = delimitateur(raw);
	pos = getpos_c(*raw, search);
	if (pos == -1)
		pos = size_stack(*raw);
	str = malloc((pos +1)* sizeof(char));
	while (i < pos)
	{
		c_tmp = pop(raw);
		str[i] = *c_tmp;
		free(c_tmp);
		i++;
	}
	if (size_stack(*raw) !=  0)
		remove_pos_c(raw,0);
	str[i] = '\0';
	return (str);
}


void	create_raw_list(t_list **str, char *line)
{// ok
	int	i;
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
{// a tester
	int	i;
	int	len;
	
	len = ft_strlen(search);
	i = 0;
	while (i < (int)size_stack(*str))
	{
		if ((ft_strncmp(getitem(*str, i),search, len) == 0 ))// 1 avant
		{
		//	if (i > 0 && (ft_strncmp(getitem(*str, i - 1),"\\",1) != 0 ))
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
			if (getitem_int(*dq, 2*(d_index - 1) +1) > (getitem_int(*sq, 2*(s_index-1)+1)))
				printf("type 3: \" \' \' \"\n");
		/* 	else
				printf("type 4: \' \" \' \"\n"); */
		}
	}
}

int	getposition(t_list *top, char *item)
{// ok?
	int	i;
	int	len;

	len = ft_strlen(item);
	i = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->data, item, len) == 0)
			return (i);
		i++;
		top = top->next;
	}
	return (-1);
}
