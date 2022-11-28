/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:11:07 by jsollett          #+#    #+#             */
/*   Updated: 2022/11/28 16:58:38 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while(index_cmd < (int)size_stack_dico(p->cmd_d))
    {
		index = 0;
		while (index < (int)size_stack(p->struct_path.split_path))
		{
		tmp1 = NULL;
			create_raw_list(&path_tmp, getitem_c(p->struct_path.split_path, index));
			create_raw_list(&path_tmp, "/");
		 	
			d_tmp = getitem_dico(p->cmd_d, index_cmd);
            if (ft_strncmp(d_tmp->value, "", 1) == 0)// ajout 2811
            {
                delete(&path_tmp);
                delete_dico(&d_tmp);
                break ;
            }
            create_raw_list(&path_tmp, d_tmp->value);
			//create_raw_list(&path_tmp, getitem_c(p->word, index_cmd));
			// ^^
			// modif vv
			path_tmp = reverse(&path_tmp);
			if (ft_strncmp(d_tmp->key, " ", 1) == 0) 
				tmp1 = getword1(&path_tmp, " ");
			else // a verifier avec ' ou ""
				tmp1 = getall(&path_tmp);
			if (!access( tmp1, X_OK))
				push(&p->struct_cmd.cmd, tmp1);
			free(tmp1);
			delete(&path_tmp);
			delete_dico(&d_tmp);
			index++;
		}	
		index_cmd++;
    }
}