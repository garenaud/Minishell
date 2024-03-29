/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:53:17 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/26 15:22:06 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bultin_cd(t_exe *curr, t_parser *p)
{
	char	cwd[PATH_MAX];
	int		pos;

	getcwd(cwd, sizeof(cwd));
	if (chdir(curr->cmd_tab[1]) == 0)
	{
		pos = get_key(p->envvar, "OLDPWD");
		remove_pos_dico(&p->envvar, pos);
		push_dico(&p->envvar, "OLDPWD", cwd);
		getcwd(cwd, sizeof(cwd));
		pos = get_key(p->envvar, "PWD");
		remove_pos_dico(&p->envvar, pos);
		push_dico(&p->envvar, "PWD", cwd);
		p->return_val = 0;
	}
	else
	{
		perror(curr->cmd_tab[1]);
		p->return_val = 1;
	}
	return (0);
}
