/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 09:33:02 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/11 14:11:38 by jsollett         ###   ########.fr       */
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


/*void	add_space(t_parser *p)
{
	t_list	*tmp;

	tmp = NULL;
	while (size_stack(p->raw))
	{
		if ((ft_strncmp(getitem(p->raw, 0), "|", 1) == 0)
			&& ft_strncmp(getitem(p->raw, 1), "|", 1) == 0)
		{
			push(&tmp, " ");
			transfer_c(&p->raw, &tmp);
			transfer_c(&p->raw, &tmp);
			push(&tmp, " ");
		}
		else if ((ft_strncmp(getitem(p->raw, 0), "|", 1) == 0)
			&& ft_strncmp(getitem(p->raw, 1), "|", 1) != 0)
		{
			push(&tmp, " ");
			transfer_c(&p->raw, &tmp);
			push(&tmp, " ");
		}
		else
		{
			transfer_c(&p->raw, &tmp);
		}
	}
	while (size_stack(tmp))
	{
		transfer_c(&tmp, &p->raw);
	}
	printf(YEL);
	printll(p->raw);
	printf(ENDC);
}*/

/*void	remove_successive_key(t_parser *p)
{// ? ne check pas parite ' ou "
	int	count;
	int	index;

	count = 0;
	index = 0;
	while (index < (int)size_stack(p->raw))
	{
		if (ft_strncmp(getitem_c(p->raw, index), p->cmd_d_tmp->value, 1) == 0)
			count++;
		index++;
	}
	if (count % 2 == 0)
	{
		index = 0;
		while (index < (int)size_stack(p->raw))
		{
			if (ft_strncmp(getitem_c(p->raw, index), p->cmd_d_tmp->value, 1) == 0)
			{
				remove_pos_c(&p->raw, index);
			}
			index++;
		}
	}
	p->raw = reverse(&p->raw);
}*/

/*void	trim_list_c(t_list **str, char *s)
{
	while (size_stack(*str) && ft_strncmp(getitem_c(*str, 0), s, 1) == 0)
		remove_pos_c(str, 0);
	while (size_stack(*str) && ft_strncmp(getitem_c(*str, size_stack(*str) - 1), s, 1) == 0)
		remove_pos_c(str, size_stack(*str) - 1);
}*/

void	inclusion(t_list_i **sq, t_list_i **dq, int s_index, int d_index)
{// essai, pour trouver la plage entre ' ' et entre " " a tster
	if ((s_index <= (int)size_stack_int(*sq) / 2) && (d_index <= (int)size_stack_int(*dq) / 2))
	{
		if (getitem_int(*sq, 2*(s_index-1)) < (getitem_int(*dq, 2*(d_index-1))))
		{
			if (getitem_int(*sq, 2*(s_index-1) + 1) > (getitem_int(*dq, 2*(d_index-1) +1)))
				printf("type 1: \' \" \" \'\n");
		}
		else
			printf("type 2: \" \' \" \'\n"); */
		else
		if (getitem_int(*dq, 2*(d_index-1)) < (getitem_int(*sq, 2*(s_index - 1))))
			{
				if (getitem_int(*dq, 2 * (d_index - 1) + 1) > (getitem_int(*sq, 2 * (s_index - 1) + 1)))
					printf("type 3: \" \' \' \"\n");
			}
	}
}

void	create_parsing_dico(t_parser *p)
{
	while (size_stack(p->raw) && size_stack_int(p->flag))
	{
		p->util.i1 = pop_int(&p->flag);
		p->util.c_tmp = pop(&p->raw);
		if (!(p->util.i1 == 32 && ft_strncmp(p->util.c_tmp, " ", 1) == 0))// avant 0 pour p->util.i1, -1 <>getitem
			push(&p->util.tmp, p->util.c_tmp);
		free(p->util.c_tmp);
		if (size_stack(p->raw) == 0)
		{// pb
			if (p->util.i1 == 0)
				p->util.key = "0";
			if (p->util.i1 == 1)
				p->util.key = "1";
			if (p->util.i1 == 2)
				p->util.key = "2";
			if (p->util.i1 == 3)//
				p->util.key = "3";//
			if (p->util.i1 == 4)//
				p->util.key = "4";//
			if (p->util.i1 == 5)//
				p->util.key = "5";//
			if (p->util.i1 == 6)//
				p->util.key = "6";//
			if (p->util.i1 == 7)//
				p->util.key = "7";//
			if (p->util.i1 == 32)//
				p->util.key = "32";//
			p->util.c_tmp = getall(&p->util.tmp);
			push_dico(&p->cmd_d, p->util.key, p->util.c_tmp);
			free(p->util.c_tmp);
			break ;
		}
		while (size_stack(p->raw) && size_stack_int(p->flag))// pb
		{// a mettre condition pour separer suivant space
			p->util.i2 = getitem_int(p->flag, 0);
			pop_int(&p->flag);
			p->util.c_tmp = pop(&p->raw);
			push(&p->util.tmp, p->util.c_tmp);
			if ((p->util.i2 != p->util.i1) || (p->util.i1 == 0 && ft_strncmp(p->util.c_tmp, " ", 1) == 0) || size_stack(p->raw) == 0)
			{
				if (p->util.i1 == 0)
					p->util.key = "0";
				if (p->util.i1 == 1)
					p->util.key = "1";
				if (p->util.i1 == 2)
					p->util.key = "2";
				if (p->util.i1 == 3)//
					p->util.key = "3";//
				if (p->util.i1 == 4)//
					p->util.key = "4";//
				if (p->util.i1 == 5)//
					p->util.key = "5";//
				if (p->util.i1 == 6)//
					p->util.key = "6";//
				if (p->util.i1 == 7)//
					p->util.key = "7";//
				if (p->util.i1 == 32)//
					p->util.key = "32";//
				if (size_stack(p->raw))
				{// debug ok remet ce qui a ete enleve
					free(p->util.c_tmp);
					p->util.c_tmp = pop(&p->util.tmp);
					push(&p->raw, p->util.c_tmp);// leak
					push_int(&p->flag, p->util.i2);// leak
					free(p->util.c_tmp);
				}
				else
					free(p->util.c_tmp);
				p->util.tmp = reverse(&p->util.tmp);
					//free(w_tmp);//
				p->util.c_tmp = getall(&p->util.tmp);
				printf(RED"%s\n"ENDC, p->util.c_tmp);
				delete(&p->util.tmp);
				if (ft_strlen(p->util.c_tmp))//
					push_dico(&p->cmd_d, p->util.key, p->util.c_tmp);
				//printll_dico(p->cmd_d);
				free(p->util.c_tmp);
				break ;
			}
			free(p->util.c_tmp); //l 448
		}
	}
	p->cmd_d = reverse_dico(&p->cmd_d);
	printf(RED);
	printll_dico(p->cmd_d);
	printf(ENDC);
	// delete_dico(&p->cmd_d);
}

void	check_quote_3(t_parser *p)
{
//	create_quote_list(&p->raw, &p->dquote, "\"");//
//	create_quote_list(&p->raw, &p->squote, "\'");//
	while (size_stack(p->raw))
	{
		p->util.c_tmp = pop(&p->raw);
		//p->util.c_tmp = getitem_c(p->raw, 0);
		if (ft_strncmp(p->util.c_tmp, "\"", 1) == 0)
			get_inside_dquote1(&p);
		if (ft_strncmp(p->util.c_tmp, "\'", 1) == 0)
			get_inside_squote1(&p);
		if (ft_strncmp(p->util.c_tmp, " ", 1) == 0)
			get_inside_space(p);
		else
		{
			if (ft_strncmp(p->util.c_tmp, "|", 1) == 0)
			{
				if (count_successive_c(p, "|") == 1)
					add_space_flag(p, 5);//** avant 3
				else if (count_successive_c(p, "|") == 2)
					add_2space_flag(p, 8);
				else
				{// voir comment gerer erreur
					printf("erreur\n");
					free(p->util.c_tmp);
					delete(&p->raw);
					break ;
				}
				continue ;
			}
			if (ft_strncmp( p->util.c_tmp, ">", 1) == 0)
			{// a verifier
				if (count_successive_c(p, ">") == 1)
					add_space_flag(p, 3);
				else if (count_successive_c(p, ">") == 2)
					add_2space_flag(p, 7);
				else
				{// voir comment gerer erreur, leak ok ?
					printf("erreur\n");
					free(p->util.c_tmp);
					delete(&p->raw);
					break ;
				}
				continue ;
			}
			if (ft_strncmp( p->util.c_tmp, "<", 1) == 0)
			{// a verifier
				if (count_successive_c(p, "<") == 1)
					add_space_flag(p, 4);
				else if (count_successive_c(p, "<") == 2)
					add_2space_flag(p, 6);
				else
				{// voir comment gerer erreur, leak ok ?
					printf("erreur\n");//
					free( p->util.c_tmp);
					delete(&p->raw);
					break ;
				}
				continue ;
			}
			if (ft_strlen(p->util.c_tmp))
			{
				push(&p->util.tmp, p->util.c_tmp);
				push_int(&p->flag, 0);// mod2312
			}
			free(p->util.c_tmp);
		}
	}
	p->raw = reverse(&p->util.tmp);
	p->flag = reverse_int(&p->flag);
	printf(YEL);
	print_ic(p->flag, p->raw);
	printf(ENDC"\n");
	delete(&p->util.tmp);
	clean_dico(p);
}
void	get_word_list(t_parser p)
{
	while (size_stack(p.raw))
	{
		trim_list(&p.raw);
		p.tmp = getword1(&p.raw, " ");
		if (ft_strncmp(p.tmp, "", 1))
		{
			push(&p.word, p.tmp);
			free(p.tmp);
		}
		else
		{
			printf("tmp vide= [%s]\n", p.tmp);
			free(p.tmp);
		}
	}
	p.word = reverse(&p.word);
}

void test_dico(t_parser p, char **env)
{
	int	index;

	create_dico_list(&p.dico, env);
	printll_dico(p.dico);
	index = get_key(p.dico, "CPPFLAGS");
	p.dico_tmp = getitem_dico(p.dico, index);
	printll_dico(p.dico_tmp);
	delete_dico(&p.dico_tmp);
	remove_pos_dico(&p.dico, index);
	printll_dico(p.dico);
	delete_dico(&p.dico);
}

void	check_for_dollar(t_parser *p)
{
	int	pos_dollar;
	int	consecutive_dollar;

	pos_dollar = getpos_c(p->raw, "$");
	consecutive_dollar = count_successive_c(p, "$");
	if (ft_strncmp(getitem_c(p->raw, pos_dollar + consecutive_dollar), " ", 1))
		check_for_envvar(p);
}

void	create_path_access(t_parser *p)
{// version 1: tient compte des "" et '' (a verifier)
	char	*tmp1;
	int		index;
	int		index_cmd;
	t_list	*path_tmp;
	t_dico	*d_tmp;

	d_tmp = NULL;
	path_tmp = NULL;
	d_tmp = getitem_dico(p->cmd_d, 0);
	index = 0;
	index_cmd = 0;
	if (!access(d_tmp->value, F_OK | X_OK))
	printf("cmd line [%s] valid \n", d_tmp->value);// mettre en boucle...

	delete_dico(&d_tmp);
	d_tmp = NULL;
	while (index_cmd < (int)size_stack_dico(p->cmd_d))
	{
		index = 0;
		while (index < (int)size_stack(p->struct_path.split_path))
		{
			tmp1 = NULL;
			//tmp1 = create_candidate(p, index, index_cmd);
			printf("\n%s has adress %p \n", tmp1, tmp1);//
			create_raw_list(&path_tmp, getitem_c(p->struct_path.split_path, index));
			create_raw_list(&path_tmp, "/");
			d_tmp = getitem_dico(p->cmd_d, index_cmd);
			if (ft_strncmp(d_tmp->value, "", 1) == 0)
			{
				printf("\nCREATE PATH IF\n");
				delete(&path_tmp);
				delete_dico(&d_tmp);
				break ;
			}
			create_raw_list(&path_tmp, d_tmp->value);
			path_tmp = reverse(&path_tmp);

			if (ft_strncmp(d_tmp->key, " ", 1) == 0)
				tmp1 = getword1(&path_tmp, " ");
			else
				tmp1 = getall(&path_tmp);

			if (!access(tmp1, X_OK))
				push(&p->struct_cmd.cmd, tmp1);
			free(tmp1);
			delete(&path_tmp);
			delete_dico(&d_tmp);
			index++;
		}
		index_cmd++;
	}
}

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

void	get_inside_dquote2(t_parser *p)
{// backup
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
