/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:16:24 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/23 21:12:00 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	get_path(p);
}

void	parse_it(t_parser *p)
{
	tester(p);
	//print_ic(p->util.code, p->util.raw_tmp);
	//printf("%s\n", p->line);
	create_parsing_dict(p);
	duplicate(&p->cmd_d, &p->cmd_copy);
	if (p->cmd_d)
	{
		create_path_access(p);
	}
}
