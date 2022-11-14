

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
			return (env[i]);
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
    printll(*env_list);
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

void	printll_dico(t_dico **dico)
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
