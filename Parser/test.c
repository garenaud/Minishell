/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:55:24 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/05 15:08:13 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_list(char *env[])
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

void	create_env_list(t_list **env_list, char *env[])
{//leak
	int	i;

	i = 0;
	while (*(env + i) != NULL)
	{
		push(env_list, env[i]);
		i++;
	}
	*env_list = reverse(env_list);
}

void	printll_dico(t_dico *dico)
{
	printf("start dico");
	while (dico)
	{
		printf("-->[%s][%s]\n", (dico->key), (dico->value));
		dico = dico->next;
	}
	printf("-->[end]\n");
}

char	*put_key(int *i, int *j, char *env[])
{
	t_list	*tmp;
	char	*key;

	tmp = NULL;
	while (env[*i][*j] != '=')
	{
		push(&tmp, &env[*i][*j]);
		(*j)++;
	}
	tmp = reverse(&tmp);
	key = getword1(&tmp, " ");
	delete(&tmp);
	return (key);
}

char	*put_value(int *i, int *j, char *env[])
{
	t_list	*tmp;
	char	*value;

	tmp = NULL;
	(*j)++;
	while (env[*i][*j] != '\0')
	{
		push(&tmp, &env[*i][*j]);
		(*j)++;
	}
	tmp = reverse(&tmp);
	value = getword1(&tmp, " ");
	delete(&tmp);
	return (value);
}

void	create_dico_list(t_dico **dico, char *env[])
{
	int		i;
	int		j;
	t_list	*tmp;
	char	*s1;
	char	*s2;

	tmp = NULL;
	i = 0;
	while (*(env + i) != NULL)
	{
		j = 0;
		s1 = put_key(&i, &j, env);
		s2 = put_value(&i, &j, env);
		push_dico(dico, s1, s2);
		free(s1);
		free(s2);
		i++;
	}
}

void	get_inside_dquote1(t_parser **p)
{
	if ((size_stack_int((*p)->dquote) % 2) == 0)
	{
		(*p)->util.position = -pop_int(&(*p)->dquote) + pop_int(&(*p)->dquote) - 1;
		free((*p)->util.c_tmp);
		while ((*p)->util.position)
		{
			(*p)->util.c_tmp = pop(&(*p)->raw);
			push(&(*p)->util.tmp, (*p)->util.c_tmp);
			push_int(&(*p)->flag, 2);
			if (ft_strncmp((*p)->util.c_tmp, "\'", 1) == 0)
				pop_int(&(*p)->squote);
			free((*p)->util.c_tmp);
			(*p)->util.position--;
		}
		remove_pos_c(&(*p)->raw, 0);
		(*p)->util.c_tmp = ft_strdup("");
	}
	else
	{// pb malloc
		free((*p)->util.c_tmp);
		printf("synatx error\n");
	}
}

void	get_inside_squote1(t_parser **p)
{
	printf("\'");
	if ((size_stack_int((*p)->squote) % 2) == 0)
	{
		(*p)->util.position = -pop_int(&(*p)->squote) + pop_int(&(*p)->squote) - 1;
		free((*p)->util.c_tmp);
		while ((*p)->util.position)
		{
			(*p)->util.c_tmp = pop(&(*p)->raw);
			push(&(*p)->util.tmp, (*p)->util.c_tmp);
			push_int(&(*p)->flag, 1);
			if (ft_strncmp((*p)->util.c_tmp, "\"", 1) == 0)
				pop_int(&(*p)->dquote);
			free((*p)->util.c_tmp);
			(*p)->util.position--;
		}
		remove_pos_c(&(*p)->raw, 0);
		(*p)->util.c_tmp = ft_strdup("");
	}
	else
	{// a ameliorer pb malloc
		free((*p)->util.c_tmp);
		printf("synatx error\n");
	}
}

void	clean_dico_32(t_parser **p, t_list **raw_tmp, t_list_i **flag_tmp)
{
	char	*tmp;
	int		flag;

	tmp = pop(&(*p)->raw);
	push(&(*raw_tmp), tmp);
	free(tmp);
	flag = pop_int(&(*p)->flag);
	push_int(&(*flag_tmp), flag);
	while (getitem_int((*p)->flag, 0) == 32)
	{
		remove_position_int(&(*p)->flag, 0);
		remove_pos_c(&(*p)->raw, 0);
	}
}

void	clean_dico_helper(t_parser **p, t_list **raw_tmp, t_list_i **flag_tmp)
{
	char	*tmp;
	int		flag;

	tmp = pop(&(*p)->raw);
	push(&(*raw_tmp), tmp);
	free(tmp);
	flag = pop_int(&(*p)->flag);
	push_int(&(*flag_tmp), flag);
}

void	clean_dico(t_parser *p)
{
	t_list		*raw_tmp;
	t_list_i	*flag_tmp;

	raw_tmp = NULL;
	flag_tmp = NULL;
	while (size_stack(p->raw))
	{
		if (getitem_int(p->flag, 0) == 32)
		{
			clean_dico_32(&p, &raw_tmp, &flag_tmp);
		}
		else
		{
			clean_dico_helper(&p, &raw_tmp, &flag_tmp);
		}
	}
	p->raw = reverse(&raw_tmp);
	p->flag = reverse_int(&flag_tmp);
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

void	check_for_envvar(t_parser *p)
{
	t_list		*raw_tmp;
	t_list		*raw_tmp1;
	t_list		*key_raw;
	t_list_i	*flag_tmp;
	t_dico		*env;
	char		*tmp;
	int			pos;
	int			status; // 0 aucun ,1 un squote, 2 dquote
	int			pos_dollar;

	status = 0;
	raw_tmp = NULL;
	raw_tmp1 = NULL;
	flag_tmp = NULL;
	key_raw = NULL;
	env = NULL;
	if (getpos_c(p->raw, "$") != -1)// if
	{
		printf("$ detecte a la pos %d \n", getpos_c(p->raw, "$"));
		while (size_stack(p->raw))
		{
			printf("entree while: status %d'\n", status);
			pos = 0;
			pos_dollar = getpos_c(p->raw, "$");
			if (pos_dollar == -1)
				break ;
			while (pos <= pos_dollar)// avant = sinon boucle infini
			{
				if (size_stack(p->raw) && ft_strncmp(getitem_c(p->raw, 0), "$", 1) == 0)
				{// pose un pb, le remove
					remove_pos_c(&p->raw, 0);
					pos++;
					continue ;
				}
				if (size_stack(p->raw) && ft_strncmp(getitem_c(p->raw, 0), "'", 1) == 0 && status != 2)// cas non /"/'
				{
					if (size_stack_int(p->squote) % 2 == 0)
					{
						transfer_c(&p->raw, &raw_tmp);
						pos++;
						while (ft_strncmp(getitem_c(p->raw, 0), "'", 1) != 0)
						{
							transfer_c(&p->raw, &raw_tmp);
							pos++;
						}
						//transfer_c(&p->raw, &raw_tmp);//segf
						//pos++;// segf
						status = 1;
					}
					/*else
						printf("erreur\n"); */
				}
		//		else
				if (size_stack(p->raw) && ft_strncmp(getitem_c(p->raw, 0), "\"", 1) == 0)
				{
					status = 2;
				}
				printf("\t        end w1 status %d\n", status);
				transfer_c(&p->raw, &raw_tmp);
				pos++;
			}
			p->util.i1 = status ;
			p->util.i2 = p->util.i1;
			while (size_stack(p->raw) && p->util.i1 == p->util.i2 && ft_strncmp(getitem_c(p->raw,0), "$", 1) != 0)
			{
				if (ft_strncmp(getitem_c(p->raw, 0), "\'", 1) == 0)
				{
					printf("1");
					p->util.i2 = 1;
					//status = 0;// test 2912
					break ;
				}
				else
				if (ft_strncmp(getitem_c(p->raw, 0), "\"", 1) == 0)
				{
					printf("2");
					p->util.i2 = 2;
					break ;
				}
			/*	if (status == 1)
				{// simple quote
					transfer_c(&p->raw, &raw_tmp);
					printf(RED"\n status = 1\n"ENDC);
				}
				else*/
				//if (getpos_c(p->raw, "$") != -1) // probleme
				{// double quote or nothing
					if (ft_isalnum(getitem_c(p->raw, 0)[0])) //
						transfer_c(&p->raw, &key_raw);
					else
						transfer_c(&p->raw, &raw_tmp1);// je pense faux
				}
				//else
				//	transfer_c(&p->raw, &raw_tmp);// probleme
			}
			//if (getpos_c(p->raw, "$") != -1)
			{
			key_raw = reverse(&key_raw);
			tmp = getall(&key_raw);
			printf("getall -> [%s], status = %d\n", tmp, status);
			if (get_key(p->envvar, tmp) != -1)
			{
			//	printf("key searching...pos=[%d]\n", get_key(p->envvar, tmp));
				env = getitem_dico(p->envvar, get_key(p->envvar, tmp));
				free(tmp);
				printf("value = [%s]\n", env->value);
			//	printf("env adress %p\n", env);
				tmp = ft_strdup(env->value);
				create_raw_list(&raw_tmp ,tmp);// doute
				free(tmp);// rajout 2812
				raw_tmp1 = reverse(&raw_tmp1);// 2912 test corr 1 inversion
				tmp = getall(&raw_tmp1);// rajout 2812
				create_raw_list(&raw_tmp ,tmp); // rajout 2812
				free(tmp);//
				delete_dico(&env);//
			}
			}
/*			else
			{// test 2912 faux
				printf("\n TEST \n");
			//	free(tmp);
				raw_tmp1 = reverse(&raw_tmp1);
			//	tmp = getall(&raw_tmp1);
				create_raw_list(&raw_tmp, tmp);
				free(tmp);
				tmp = getall(&raw_tmp1);
				create_raw_list(&raw_tmp, tmp);
				free(tmp);
			}*/
			status = 0;//test 2912
			printf("sortie while \n");
			while (size_stack(raw_tmp1))//
				transfer_c(&raw_tmp1, &raw_tmp);//
		}
		if (getpos_c(p->raw, "$") == -1)
		{
			while (size_stack(p->raw))
			{
				transfer_c(&p->raw, &raw_tmp);
			}
		}
		p->raw = reverse(&raw_tmp);
	}
}

// les flag space etaient a 0 puis -1 -><- getitem
void	add_space_pipe(t_parser *p)
{
	push(&p->util.tmp, " ");
	push_int(&p->flag, 32);
	push(&p->util.tmp, p->util.c_tmp);
	push_int(&p->flag, 3);// 0 avant
	push(&p->util.tmp, " ");
	push_int(&p->flag, 32);
	free(p->util.c_tmp);
}

void	add_space_flag(t_parser *p, int flag)
{
	push(&p->util.tmp, " ");
	push_int(&p->flag, 32);
	push(&p->util.tmp, p->util.c_tmp);
	push_int(&p->flag, flag);// 3 |, 4 <,  5> avant
	push(&p->util.tmp, " ");
	push_int(&p->flag, 32);
	free(p->util.c_tmp);
	//p->util.c_tmp = NULL;//
}

void	add_2space_flag(t_parser *p, int flag)
{// 6 << 7 >>
	p->util.c_tmp1 = pop(&p->raw);
	push(&p->util.tmp, " ");
	push_int(&p->flag, 32);
	push(&p->util.tmp, p->util.c_tmp);
	push_int(&p->flag, flag);
	push(&p->util.tmp, p->util.c_tmp1);
	push_int(&p->flag, flag);
	push(&p->util.tmp, " ");
	push_int(&p->flag, 32);
	free(p->util.c_tmp);
	free(p->util.c_tmp1);
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
	while (size_stack(p->struct_path.path_raw))
	{
		trim_list(&p->struct_path.path_raw);
		tmp = getpath(&p->struct_path.path_raw);
		if (ft_strncmp(tmp, "", 1))
		{
			push(&p->struct_path.split_path, tmp);
			free(tmp);
		}
		else
			free(tmp);
	}
	p->struct_path.split_path = reverse(&p->struct_path.split_path);
}



static void cpd1_key(t_parser *p)
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

void	cpd1(t_parser *p)
{
	while (size_stack(p->raw) && size_stack_int(p->flag))
	{
		p->util.i1 = getitem_int(p->flag, 0);
		p->util.i2 = p->util.i1;
		while (size_stack(p->raw) && p->util.i2 != 32)
		{
			p->util.c_tmp = pop(&p->raw);
			push(&p->util.tmp, p->util.c_tmp);
			free(p->util.c_tmp);
			p->util.i2 = pop_int(&p->flag);
			p->util.i2 = getitem_int(p->flag, 0);
		}
		p->util.tmp = reverse(&p->util.tmp);
		p->util.c_tmp = getall(&p->util.tmp);
		cpd1_key(p);
		if (ft_strlen(p->util.c_tmp))
			push_dico(&p->cmd_d, p->util.key, p->util.c_tmp);
		free(p->util.c_tmp);
		remove_position_int(&p->flag, 0);
		remove_pos_c(&p->raw, 0);
		delete(&p->util.tmp);
	}
	p->cmd_d = reverse_dico(&p->cmd_d);
	printll_dico(p->cmd_d);
}
