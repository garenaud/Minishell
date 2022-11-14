


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
{// ok
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
		if (ft_strncmp(top->key, item, ft_strlen(item)) == 0)
			return (i);
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
		if (ft_strncmp(top->value, item, ft_strlen(item)) == 0)
			return (i);
		top = top->next;
		i++;
	}
	return (-1);
}

int	transfer_dico(t_dico **start, t_dico **end)
{
	t_dico  *tmp;
	
	if (size_stack_dico(*start) >= 1)
	{
        tmp  = pop_dico(start);
		push_dico(end, tmp->key, tmp->value);
		// free(tmp);
		delete_dico(&tmp);
		return (1);
	}
	return (0);
}

int	remove_pos_dico(t_dico **top, size_t pos)
{
	t_dico	*tmp;
    t_dico  *c_tmp;

	tmp = NULL;
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
		//free(c_tmp);
		delete_dico(&c_tmp);
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
	if (pos >= size_stack_dico(top))
		return (NULL);
	else
	{
		while (pos > 0)
		{
			top = top->next;
			pos--;
		}
		return (top);
	}
}