/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:11:07 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/16 17:29:34 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_candidate(t_parser *p, int index, int index_cmd)
{
	char	*tmp1;
	t_dico	*d_tmp;
	t_list	*path_tmp;

	tmp1 = NULL;
	d_tmp = NULL;
	path_tmp = NULL;
	create_raw_list(&path_tmp, getitem_c(p->struct_path.split_path, index));
	create_raw_list(&path_tmp, "/");
	d_tmp = getitem_dico(p->cmd_d, index_cmd);
	create_raw_list(&path_tmp, d_tmp->value);
	path_tmp = reverse(&path_tmp);
	if (ft_strncmp(d_tmp->key, " ", 1) == 0)
		tmp1 = getword1(&path_tmp, " ");
	else
		tmp1 = getall(&path_tmp);
//	printf("%p\t%p\n", path_tmp, d_tmp);
//	delete(&path_tmp);
	delete_dico(&d_tmp);
	return (tmp1);
}

void	create_path_access(t_parser *p)
{
	char	*tmp1;
	int		index;
	int		index_cmd;

	index = 0;
	index_cmd = 0;
	while (index_cmd < (int)size_stack_dico(p->cmd_d))
	{
		index = 0;
		while (index < (int)size_stack(p->struct_path.split_path))
		{
			tmp1 = NULL;
			tmp1 = create_candidate(p, index, index_cmd);
			if (!access(tmp1, X_OK))
				push(&p->struct_cmd.cmd, tmp1);
			free(tmp1);
			index++;
		}
		index_cmd++;
	}
}

/*t_dico	*shift(t_parser *p, int pos)
{// a tester
	int		count;
	t_dico	*res;

	count = 0;
	p->cmd_d = reverse(&p->cmd_d);
	while (pos < (int)size_stack_dico(p->cmd_d))
	{
		res = getitem_dico(p->cmd_d, pos);
		if (ft_strncmp(res->value, "|", 1) == 0)
		{
			count++;
			continue ;
		}
		if (count == pos)
		{
			delete_dico(res);
			return (getitem_dico(p->cmd_d, pos + 1));
		}
		delete_dico(res);
		pos++;
	}
	return (NULL);
}

char	*concat(t_parser *p)
{
	char	*tmp1;
	t_list	*path_tmp;

	path


}*/

void	create_path_access_backup(t_parser *p)
{// version 1: tient compte des "" et '' (a verifier)
	char	*tmp1;
	int		index;
	int		index_cmd;
//	t_list	*path_tmp;
	t_dico	*d_tmp;

	d_tmp = NULL;
//	path_tmp = NULL;
	d_tmp = getitem_dico(p->cmd_d, 0);
	index = 0;
	index_cmd = 0;
	if (!access(d_tmp->value, F_OK | X_OK))
	printf("cmd line [%s] valid \n", d_tmp->value);// mettre en boucle...
	delete_dico(&d_tmp);
	//d_tmp = NULL;
	while (index_cmd < (int)size_stack_dico(p->cmd_d))
	{
		index = 0;
		while (index < (int)size_stack(p->struct_path.split_path))
		{
			tmp1 = NULL;
			tmp1 = create_candidate(p, index, index_cmd);
			if (!access(tmp1, X_OK))
				push(&p->struct_cmd.cmd, tmp1);
			free(tmp1);
	//		delete(&path_tmp);
	//		delete_dico(&d_tmp);
			index++;
		}
		index_cmd++;
	}
}
