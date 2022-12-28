/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 09:33:02 by jsollett          #+#    #+#             */
/*   Updated: 2022/12/27 09:38:26 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	get_inside_squote(t_parser *p)
{
		printf("\'");
	if ((size_stack_int(p->squote) % 2) == 0)
	{
		p->util.position = -pop_int(&p->squote) + pop_int(&p->squote) - 1;
		free(p->util.c_tmp);
		while (p->util.position)
		{
			p->util.c_tmp = pop(&p->raw);
			push(&p->util.tmp, p->util.c_tmp);
			push_int(&p->flag, 1);
			if (ft_strncmp(p->util.c_tmp, "\"", 1) == 0)
				pop_int(&p->dquote);
			free(p->util.c_tmp);
			p->util.position--;
		}
		remove_pos_c(&p->raw, 0);
	}
	else
	{// a ameliorer
		free(p->util.c_tmp);
		printf("synatx error\n");
	}
}

void	get_inside_dquote(t_parser *p)
{
	printf("\"");
	if ((size_stack_int(p->dquote) % 2) == 0)
	{
		p->util.position = -pop_int(&p->dquote) + pop_int(&p->dquote) - 1;
		free(p->util.c_tmp);
		//remove_pos_c(&p->raw, 0);//
		while (p->util.position)
		{
			p->util.c_tmp = pop(&p->raw);
			push(&p->util.tmp, p->util.c_tmp);
			push_int(&p->flag, 2);
			if (ft_strncmp(p->util.c_tmp, "\'", 1) == 0)
				pop_int(&p->squote);
			free(p->util.c_tmp);
			p->util.position--;
		}
		remove_pos_c(&p->raw, 0);
	}
	else
	{
		free(p->util.c_tmp);
		printf("synatx error\n");
	}
}

void	check_quote_1(t_parser *p)
{
	int		q_index;
	int		index;
	int		flag;
	char	*c_tmp;
	int		start;
	//int		end;

	index = 0;
	start = 0;
	flag = 0;
	c_tmp = NULL;
	while (index < (int)size_stack(p->raw))
	{
		if (size_stack_int(p->dquote) && size_stack_int(p->squote))
		{// deux piles existent
			if (getitem_int(p->dquote, 0) < getitem_int(p->squote, 0))
			{
				q_index = pop_int(&p->dquote);
				flag = 8;
			}
			else
			{
				q_index = pop_int(&p->squote);
				flag = 4;
			}
		}
		else if (size_stack_int(p->dquote) && size_stack_int(p->squote) == 0)
		{
			q_index = pop_int(&p->dquote);
			flag = 2;
		}
		else if (size_stack_int(p->dquote) == 0 && size_stack_int(p->squote))
		{
			q_index = pop_int(&p->squote);
			flag = 1;
		}
		else if (size_stack_int(p->dquote) == 0 && size_stack_int(p->squote) == 0)
		{
			q_index = size_stack(p->raw);
			flag = 0;
		}
		while (start == 0 && index < q_index)
		{// debut du scan
			c_tmp = getitem_c(p->raw, index);
			push_dico(&p->check, "0", c_tmp);
			//free(c_tmp);
			index++;
		}
		while (flag == 0 && index < q_index)
		{
			c_tmp = getitem_c(p->raw, index);
			push_dico(&p->check, "0", c_tmp);
			//free(c_tmp);
			index++;
		}
		while (flag == 1 && index <= q_index && index > start)
		{
			c_tmp = getitem_c(p->raw, index);
			push_dico(&p->check, "1", c_tmp);
			//free(c_tmp);
			index++;
		}
		while (flag == 2 && index <= q_index && index > start)
		{
			c_tmp = getitem_c(p->raw, index);
			push_dico(&p->check, "2", c_tmp);
			//free(c_tmp);
			index++;
		}
		while (flag == 4 && index <= q_index && index > start)
		{
			c_tmp = getitem_c(p->raw, index);
			push_dico(&p->check, "4", c_tmp);
			//free(c_tmp);
			index++;
		}
		while (flag == 8 && index <= q_index && index > start)
		{
			c_tmp = getitem_c(p->raw, index);
			push_dico(&p->check, "8", c_tmp);
			//free(c_tmp);
			index++;
		}
		start = q_index;
	}
	p->check = reverse_dico(&p->check);
	printf(PURP);
	printll_dico(p->check);
	printf(ENDC);
}
