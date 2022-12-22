/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 08:20:22 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/22 17:13:58 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_exe(t_parser *p)
{
	int	i;
	int	j;
	
	j = 0;
	int size;
	int	nb_pipe;
	t_exe	*curr;
	nb_pipe = checknb_pipe(p->cmd_line);
	size = checknb_arg(p->cmd_line);
	curr = init_exe_list(size);
	p->cmd_exe = curr;
	while (j <= nb_pipe)
	{
		size = checknb_arg(p->cmd_line);
		i = 0;
		while (i < size)
		{
			curr->cmd_tab[i] = ft_strdup(p->cmd_line->value);
			remove_pos_dico(&p->cmd_line, 0);
			i++;
		}
		curr->cmd_tab[i] = NULL;
		remove_pos_dico(&p->cmd_line, 0);	
		if (j != nb_pipe)
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

