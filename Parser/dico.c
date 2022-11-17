


// test pour les fcn dico
#include "../minishell.h"

void	push_dico(t_dico **top, char *key, char *value)
{// ok
	t_dico	*tmp;
	
	tmp = malloc(sizeof(t_dico));
	if (!tmp)
		return;
	tmp->key = ft_strdup(key);
    tmp->value = ft_strdup(value);
	tmp->next = *top;
	*top = tmp; //?
}

t_dico	*pop_dico(t_dico **top)
{// premier jet
	t_dico	*tmp;
    t_dico  *result;
//	char	*key;
//  char    *value;
	
	if (*top == NULL)
	{
		printf("pop Stack empty\n");
		return (NULL);
		exit (0);
	}
    result = malloc(sizeof(t_dico));
	if (!result)
    {
		return (NULL);
    }
    tmp = *top;
	result->key = ft_strdup(tmp->key);
    result->value = ft_strdup(tmp->value);
	*top = (*top)->next;
	free(tmp->key);
    free(tmp->value);
	free(tmp);
	return (result);
}

void	delete_dico(t_dico **top)
{// probleme segfault
	t_dico	*tmp;

	if (*top == NULL)
		return;
	while (*top != NULL)
	{
	
	 	tmp = *top;
		*top = (*top)->next;
		free(tmp->key);
        free(tmp->value);
		free(tmp);
	}
}

size_t	size_stack_dico(t_dico *top)
{
	size_t	size;

	size = 0;
	while (top != NULL)
	{
		size++;
		top = (top)->next;
	}
	return (size);
}

int	get_key(t_dico *top, char *item)
{
	int	i;

	i = 0;
	
	while (top != NULL)
	{
		if ((ft_strncmp(top->key, item, ft_strlen(top->key)) == 0) && (ft_strlen(top->key) == ft_strlen(item)))
		{
			printf("\nTrouve %d\n", i);
				return (i);
		}
		top = top->next;
		i++;
	}
	
	return (-1);
}

int	get_value(t_dico *top, char *item)
{
	int	i;

	i = 0;
	while (top != NULL)
	{
		if ((ft_strncmp(top->value, item, ft_strlen(item)) == 0) && (ft_strlen(top->value) == ft_strlen(item)))
			return (i);
		top = top->next;
		i++;
	}
	
	return (-1);
}

int	transfer_dico(t_dico **start, t_dico **end)
{
	t_dico  *tmp;
	
	tmp = NULL;
	printf("*****");
	if (size_stack_dico(*start) >= 1)
	{
        tmp  = pop_dico(start);
		push_dico(end, tmp->key, tmp->value);
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		//delete_dico(&tmp);
		return (1);
	}
	return (0);
}

int	remove_pos_dico(t_dico **top, size_t pos)
{
	t_dico	*tmp;
    t_dico  *c_tmp;

	tmp = NULL;
	c_tmp = NULL;
	if (pos >= size_stack_dico(*top))
		return (-1);
	else
	{
		while (pos > 0)
		{
			transfer_dico(top, &tmp);
			pos--;
		}
	    c_tmp = pop_dico(top);//
		free(c_tmp->key);
		free(c_tmp->value);
		free(c_tmp);

		//delete_dico(&c_tmp);
		while (tmp != NULL)
		{
			transfer_dico(&tmp, top);
		}
		return (0);
	}
}

t_dico	*reverse_dico(t_dico **top)
{// ok
	t_dico	*tmp;
	t_dico	*c_tmp;
	
	//c_tmp = NULL;
	tmp = NULL;
	while (*top != NULL)
	{
		c_tmp = NULL;
		c_tmp = pop_dico(top);
		push_dico(&tmp, c_tmp->key, c_tmp->value);
	 	free(c_tmp->key);
        free(c_tmp->value); 
	//	delete_dico(&c_tmp);
	}
	return (tmp);
}

t_dico	*getitem_dico(t_dico *top, size_t pos)
{// a verifier
	t_dico	*tmp;

	tmp = malloc(sizeof(t_dico));
	if (!tmp)
		exit (-1);
	if (pos >= size_stack_dico(top))
		return (NULL);
	else
	{
		while (pos > 0)
		{
			top = top->next;
			pos--;
		}
		tmp->key = ft_strdup(top->key);
		tmp->value = ft_strdup(top->value);
		tmp->next = NULL; // tres important
		return (tmp);
	}
}

void	check_quote(t_parser *p)
{
	int	i;
	int		flag;
	char	*c_tmp;
	char	*key;
	int		taille;


	taille = size_stack_int(p->dquote);
	c_tmp = NULL;
	i = 0;
	flag = 0;
	//key = NULL;
	while (i < (int)size_stack(p->raw))
	{
		c_tmp = getitem_c(p->raw, i);
		if (flag == 0 && taille > 0 && ft_strncmp(c_tmp, "\"", 1)== 0)
		{
			key = "2";
			flag = 2;
			taille--;
			//remove_position_int(&p->dquote, 0);
		}
		else if (flag == 2 && ft_strncmp(c_tmp, "\"", 1)== 0)
		{
			key = "0";
			flag = 0;
			taille--;
			//remove_position_int(&p->dquote, 0);
		}
		push_dico(&p->check, key, c_tmp);
		i++;
	}
	p->check = reverse_dico(&p->check);
	printf(PURP);
	printll_dico(p->check);
	printf(ENDC);
	//free(c_tmp);
}