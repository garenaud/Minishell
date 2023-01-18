/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:29:42 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/18 14:37:10 by jsollett         ###   ########.fr       */
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

static void	get_path_helper(t_parser *p)
{
	t_dico	*path;
	int		pos;

	path = NULL;
	pos = get_key(p->envvar, "PATH");
	if (pos >= 0)
	{
		path = getitem_dico(p->envvar, get_key(p->envvar, "PATH"));
		p->struct_path.path = ft_strdup(path->value);
	}
	else
	p->struct_path.path = ft_strdup("");
	delete_dico(&path);
}
//modifie a tester

void	get_path(t_parser *p)
{
	char	*tmp;

	get_path_helper(p);
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
