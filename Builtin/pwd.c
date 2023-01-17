/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:25:42 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/17 09:51:07 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bultin_pwd_old(t_exe *curr, t_parser *p)
{
	t_dico	*tmp;
	int		pos;

	pos = get_key(p->envvar, "PWD");
	tmp = getitem_dico(p->envvar, pos);
	printf("%s\n",tmp->value);
	delete_dico(tmp);
	g_status = 0;
	return (0);
}

int	bultin_pwd(t_exe *curr, t_parser *p)
{
	char	cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf()
	}
	g_status = 0;
	return (0);
}
