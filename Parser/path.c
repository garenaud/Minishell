/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:11:07 by jsollett          #+#    #+#             */
/*   Updated: 2022/11/16 16:23:23 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_path_access(t_list *path, t_parser *p)
{
    char	*tmp1;
    int		index;
	int		index_cmd;
	
	index = 0;
	index_cmd = 0;
	if (!access(getitem_c(p->word, 0), F_OK | X_OK))
	printf("cmd line [%s] valid \n", getitem_c(p->word, 0));
    while(index_cmd < (int)size_stack(p->word))
    {
		index = 0;
		while (index < (int)size_stack(p->struct_path.split_path))
		{
		tmp1 = NULL;
			create_raw_list(&path, getitem_c(p->struct_path.split_path, index));
			create_raw_list(&path, "/");
			//tmp1 = NULL;
			create_raw_list(&path, getitem_c(p->word, index_cmd));
			path = reverse(&path);
			tmp1 = getword1(&path, " ");
			if (!access( tmp1, X_OK))
				push(&p->struct_cmd.cmd, tmp1);
			free(tmp1);
			index++;
		}	
		index_cmd++;
    }
}