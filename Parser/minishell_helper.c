/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:16:24 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/19 10:35:57 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// a verifier
void	init_mini(t_parser *p, char **env)
{
	p->line = NULL;
	p->envvar = NULL;
	init_pgrm(p, env);
	set_signal();
	p->signal = malloc(sizeof(struct termios));
	setup_term(p->signal);
	create_dico_list(&p->envvar, env);
	create_delim(p);
}

void	reload(t_parser *p, char **env)
{
	init_pgrm(p, env);
	get_path(p, env);
}

void	parse_it(t_parser *p)
{
	tester(p);
	create_parsing_dict(p);
	duplicate(&p->cmd_d, &p->cmd_copy);
	if (p->cmd_d)
	{
		create_path_access(p);
	}
}
