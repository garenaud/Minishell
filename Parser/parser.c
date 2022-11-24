/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:29:00 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/24 10:48:41 by jsollett         ###   ########.fr       */
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

void	trim_list_c(t_list **str, char *s)
{
	while (size_stack(*str) && ft_strncmp(getitem_c(*str, 0), s,1) == 0)
		remove_pos_c(str, 0);
	while (size_stack(*str) && ft_strncmp(getitem_c(*str, size_stack(*str) - 1), s, 1) == 0)
		remove_pos_c(str, size_stack(*str) -1 );
}

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

t_dico	*getword_2(t_list **raw, char *search)
{ //modifiee
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
	str = malloc((pos +1)* sizeof(char));
	word = malloc(sizeof(t_dico));
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
	word->next = NULL;
	word->value = str;
	word->key = ft_strdup(search);
	return (word);
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

char	*getall(t_list **raw)
{
	int 	i;
	int		pos;
	char	*str;
	char	*c_tmp;

	i = 0;	
	pos = size_stack(*raw);
	str = malloc((pos +1)* sizeof(char));
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
