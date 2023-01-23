/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:53:17 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/23 13:21:25 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bultin_cd(t_exe *curr, t_parser *p)
{// manque erreur
	char	cwd[PATH_MAX];
	int		pos;

	getcwd(cwd, sizeof(cwd));
	if (chdir(curr->cmd_tab[1]) == 0)
	{
		//printf("cd ok\n");
		pos = get_key(p->envvar, "OLDPWD");
		remove_pos_dico(&p->envvar, pos);
		push_dico(&p->envvar, "OLDPWD", cwd);
		getcwd(cwd, sizeof(cwd));
		pos = get_key(p->envvar, "PWD");
		remove_pos_dico(&p->envvar, pos);
		push_dico(&p->envvar, "PWD", cwd);
		g_status = 0;
	}
	g_status = 0;
	return (0);
}
