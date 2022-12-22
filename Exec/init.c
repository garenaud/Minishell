/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 08:20:22 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/22 22:46:03 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_exe(t_parser *p)
{
	int	i;
	int	j;
	
	j = 0;
	int size;
	t_exe	*curr;
	p->piped = checknb_pipe(p->cmd_d);
	size = checknb_arg(p->cmd_d);
	curr = init_exe_list(size);
	p->cmd_exe = curr;
	while (j <= p->piped)
	{
		size = checknb_arg(p->cmd_d);
		i = 0;
		while (i < size)
		{
			curr->cmd_tab[i] = ft_strdup(p->cmd_d->value);
			remove_pos_dico(&p->cmd_d, 0);
			i++;
		}
		curr->cmd_tab[i] = NULL;
		remove_pos_dico(&p->cmd_d, 0);	
		if (j != p->piped)
		{
			curr->next = init_exe_list(size);
			curr = curr->next;
		}
		j++;
	}
}

char	*set_and_get(t_parser *p)
{
	char	*inpt;

	inpt = NULL;
	p->piped = 0;
	//path_update(p);
	if (g_status > 4)
		p->return_val = g_status;
	g_status = WAITING;
	signal(SIGQUIT, SIG_IGN);
	inpt = readline(p->display_path);
	g_status = PARSING;
	if (inpt && ft_isprint(inpt[0]))
		add_history(inpt);
	return (inpt);
}
int	free_all(t_parser *p)
{
	if (p->cmd_exe->cmd_tab != NULL)
	{
		free_tab(p->cmd_exe->cmd_tab);
		free(p->cmd_exe->cmd_tab);
	}
	return (0);
}
