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

void	check_quote(t_parser *p)
{
	int		i;
	int		flag;
	char	*c_tmp;
	char	*key;
	int		taille;

	taille = size_stack_int(p->dquote);
	c_tmp = NULL;
	i = 0;
	flag = 0;
	key = "0";
	if (size_stack_int(p->dquote) % 2 == 0)
	{
		while (i < (int)size_stack(p->raw))
		{
			c_tmp = getitem_c(p->raw, i);
			if (flag == 0 && taille > 0 && ft_strncmp(c_tmp, "\"", 1) == 0)
			{
				push_dico(&p->check, "2", c_tmp);
				c_tmp = getitem_c(p->raw, i + 1);
				while (ft_strncmp(c_tmp, "\"", 1) != 0)
				{
					c_tmp = getitem_c(p->raw, i + 1);
					push_dico(&p->check, "2", c_tmp);
					i++;
				}
			}
			else
				push_dico(&p->check, key, c_tmp);
			i++;
		}
	}
	else
		printf("error (impair quote)\n");
	p->check = reverse_dico(&p->check);
	printf(PURP);
	printll_dico(p->check);
	printf(ENDC);
	printf("size raw = %zu, size dico = %zu\n", size_stack(p->raw), size_stack_dico(p->check));
	//free(c_tmp);
}
