

#include "../minishell.h"

char    *path_list(char *env[])
{
	int	i;

	i = 0;
	while (*(env + i) != NULL)
	{
		if (*(*(env + i)) == 'P' && *(*(env + i) + 1) == 'A'
			&& *(*(env + i) + 2) == 'T' && *(*(env + i) + 3) == 'H'
			&& *(*(env + i) + 4) == '=')
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

void    create_env_list(t_list **env_list, char *env[])
{//leak
	int	i;

	i = 0;
	while (*(env + i) != NULL)
	{
		push(env_list, env[i]);
		i++;
	}
   *env_list = reverse(env_list);
  //  printll(*env_list);
}

void    create_dico_list(t_dico **dico,  char *env[])
{//leak
	int	i;
	int	j;
	t_list	*tmp;
	char	*s1;
	char	*s2;

	tmp = NULL;
	i = 0;
	while (*(env + i) != NULL)
	{
		j = 0;
		while (env[i][j] != '=')
		{
			push(&tmp, &env[i][j]);
			j++;
		}
		tmp = reverse(&tmp);
		s1 = getword1(&tmp, " ");
		delete(&tmp);
		tmp = NULL;
		j++;
		while (env[i][j] != '\0')
		{
			push(&tmp, &env[i][j]);
			j++;
		}
		tmp = reverse(&tmp);
		s2 = getword1(&tmp, " ");
		delete(&tmp);
		push_dico(dico, s1, s2);
		free(s1);
		free(s2);
		i++;
	}
   /*  *dico = reverse_dico(dico); */
}

void	printll_dico(t_dico *dico)
{
	printf("start dico");
	while (dico)
	{
		printf("-->[%s][%s]\n", (dico->key),(dico->value));
		dico = dico->next;
	}
	printf("-->[end]\n");
}

/* void	printll_dico(t_dico **dico)
{
	t_dico	*dico_tmp;

	dico_tmp = NULL;
	while (size_stack_dico(*dico))
	{
		dico_tmp = pop_dico(dico);// ici plutot avec les ->next... pas de pop
		printf("key = %s\t\t\t\t value = %s\n", dico_tmp->key, dico_tmp->value);
		free(dico_tmp->key);
		free(dico_tmp->value);
		free(dico_tmp);
		//delete_dico(&dico_tmp);
	}
}
 */



void    check_quote_3(t_parser *p)
{
	int     index;
	char    *c_tmp;
	char    *c_tmp1;
	t_list  *raw_tmp;
    t_list  *no_quote;
	int     flag;
	int     position;

	index = 0;
    no_quote = NULL;
	c_tmp = NULL;
	c_tmp1 = NULL;
	raw_tmp = NULL;
	flag = 0;
	printf(GREEN);
	printll(p->raw);
	while (size_stack(p->raw))
	{
		c_tmp = pop(&p->raw);
		if (flag == 0 && ft_strncmp(c_tmp, "\"", 1) == 0)
		{
			flag = 2;
			// a proteger
			position = -pop_int(&p->dquote) + pop_int(&p->dquote) - 1;//
		//	push_int(&p->word_len, position);//
           // push_int(&p->flag, flag);//
            free(c_tmp);
			while (position)
			{
				c_tmp = pop(&p->raw);
				push(&raw_tmp, c_tmp);
                push_int(&p->flag, 2);//
				if (ft_strncmp(c_tmp, "\'", 1) == 0)
					pop_int(&p->squote);
				free(c_tmp);
				position--;
			}
			remove_pos_c(&p->raw, 0);
			flag = 0;
            /* // ajout pb egv

                raw_tmp = reverse(&raw_tmp);
                c_tmp = getall(&raw_tmp);// efface raw_tmp
                push_dico(&p->cmd_d, "2", c_tmp);
                free(c_tmp);
            // */
		}
		else
		if (flag == 0 && ft_strncmp(c_tmp, "\'", 1) == 0)
		{
			flag = 1;
			position = -pop_int(&p->squote) + pop_int(&p->squote) - 1;
		//	push_int(&p->word_len, position);//
          //  push_int(&p->flag, flag);//
            free(c_tmp);
			while (position)
			{
				c_tmp = pop(&p->raw);
				push(&raw_tmp, c_tmp);
                push_int(&p->flag, 1);//
				if (ft_strncmp(c_tmp, "\"", 1) == 0)
					pop_int(&p->dquote);
				free(c_tmp);
				position--;
			}
			remove_pos_c(&p->raw, 0);
			flag = 0;
		}
		else
		if (flag == 0 && ft_strncmp(c_tmp, " ", 1) == 0)
		{// ATTN
			flag = 2;
			// a proteger
			push(&raw_tmp, c_tmp);
            push_int(&p->flag, 0);
			free(c_tmp);
			
			while (ft_strncmp(getitem_c(p->raw, 0), " ", 1) == 0)
			{
				remove_pos_c(&p->raw, 0);
			}

			flag = 0;
		}
		else
		{
			flag = 0;
			if (ft_strncmp(c_tmp, "|", 1) == 0)
				{
					push(&raw_tmp, " ");
                    push_int(&p->flag, 0);
					push(&raw_tmp, c_tmp);
                    push_int(&p->flag, 0);
					push(&raw_tmp, " ");
                    push_int(&p->flag, 0);
					free(c_tmp);
					continue ;
				}
			if (ft_strncmp(c_tmp, ">", 1) == 0)  
				{
					if (ft_strncmp(getitem_c(p->raw, 0), ">", 1) == 0 )
					{
						c_tmp1 = pop(&p->raw);
						push(&raw_tmp, " ");
                        push_int(&p->flag, 0);
						push(&raw_tmp, c_tmp);
                        push_int(&p->flag, 0);
						push(&raw_tmp, c_tmp1);
                        push_int(&p->flag, 0);
						push(&raw_tmp, " ");
                        push_int(&p->flag, 0);
						free(c_tmp);
						free(c_tmp1);
						continue ;
					}
					else
					if (ft_strncmp(getitem_c(p->raw, 0), ">", 1) != 0 )
					{
						push(&raw_tmp, " ");
                        push_int(&p->flag, 0);
						push(&raw_tmp, c_tmp);
                        push_int(&p->flag, 0);
						push(&raw_tmp, " ");
                        push_int(&p->flag, 0);
						free(c_tmp);
						continue ;
					}
				}
	        if (ft_strncmp(c_tmp, "<", 1) == 0)  
				{
					if (ft_strncmp(getitem_c(p->raw, 0), "<", 1) == 0 )
					{
						c_tmp1 = pop(&p->raw);
						push(&raw_tmp, " ");
                        push_int(&p->flag, 0);
						push(&raw_tmp, c_tmp);
                        push_int(&p->flag, 0);
						push(&raw_tmp, c_tmp1);
                        push_int(&p->flag, 0);
						push(&raw_tmp, " ");
                        push_int(&p->flag, 0);
						free(c_tmp);
						free(c_tmp1);
						continue ;
					}
					else
					if (ft_strncmp(getitem_c(p->raw, 0), "<", 1) != 0 )
					{
						push(&raw_tmp, " ");
                        push_int(&p->flag, 0);
						push(&raw_tmp, c_tmp);
                        push_int(&p->flag, 0);
						push(&raw_tmp, " ");
                        push_int(&p->flag, 0);
						free(c_tmp);
						continue ;
					}
				}
			push(&raw_tmp, c_tmp);
            push_int(&p->flag, 0);
			free(c_tmp);
		}
	}
	p->raw = reverse(&raw_tmp);
    p->flag = reverse_int(&p->flag);
    if (size_stack(p->raw) == size_stack_int(p->flag))
        printf("ok\n");
    else
        printf("ko\n");
	printf(YEL);
    print_ic(p->flag, p->raw);
	//printll(raw_tmp);
	printf(ENDC);
	delete(&raw_tmp);
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
	while(index < (int)size_stack(p->raw))
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
			q_index = size_stack(p->raw);//
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
			c_tmp =  getitem_c(p->raw, index);
			push_dico(&p->check, "1", c_tmp);
			//free(c_tmp);
			index++;
		}
		while (flag == 2 && index <= q_index && index > start)
		{
			c_tmp =  getitem_c(p->raw, index);
			push_dico(&p->check, "2", c_tmp);
			//free(c_tmp);
			index++;
		}
		while (flag == 4 && index <= q_index && index > start)
		{
			c_tmp =  getitem_c(p->raw, index);
			push_dico(&p->check, "4", c_tmp);
			//free(c_tmp);
			index++;
		}
		while (flag == 8 && index <= q_index && index > start)
		{
			c_tmp =  getitem_c(p->raw, index);
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

void test_dico(t_parser p, char **env)
{
	int	index;
	create_dico_list(&p.dico, env);
	printll_dico(p.dico);
	index = get_key(p.dico, "CPPFLAGS");
	p.dico_tmp = getitem_dico(p.dico, index);
	printf("\n\n\n");
	
	printll_dico(p.dico_tmp);
	delete_dico(&p.dico_tmp);
	remove_pos_dico(&p.dico, index);
	
	printf("%p\n", p.dico);
	printll_dico(p.dico); 
	delete_dico(&p.dico);
}

void	test_env_list(t_parser p, char **env)
{
	create_env_list(&p.struct_path.env_list, env);
	delete(&p.struct_path.env_list);
}

void	get_path(t_parser *p, char **env)
{
	char	*tmp;
	
	p->struct_path.path = path_list(env);
	create_raw_list(&p->struct_path.path_raw, p->struct_path.path);
	p->struct_path.path_raw = reverse(&p->struct_path.path_raw);
	while (size_stack(p->struct_path.path_raw ))
	{
		trim_list(&p->struct_path.path_raw);
		tmp = getpath(&p->struct_path.path_raw);
		if (ft_strncmp(tmp,"", 1))
		{
			push(&p->struct_path.split_path, tmp);
			free(tmp);
		}
		else
			free(tmp);
	}
	p->struct_path.split_path = reverse(&p->struct_path.split_path);
	printll(p->struct_path.split_path);
}

void	get_word_list(t_parser p)
{// copie de la 1ere version
	while (size_stack(p.raw ))
	 	{
			trim_list(&p.raw);
			p.tmp = getword1(&p.raw, " ");
			if (ft_strncmp(p.tmp,"", 1))
			{
				push(&p.word,p.tmp);
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