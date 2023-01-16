/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:19:17 by jsollett          #+#    #+#             */
/*   Updated: 2022/12/21 10:24:47 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
