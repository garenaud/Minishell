/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:31:49 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/23 16:06:01 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_raw_list_and_free(t_list **str, char *line)
{
	int		i;
	char	tmp[2];

	i = 0;
	while (line[i] != '\0')
	{
		tmp[0] = line[i];
		tmp[1] = '\0';
		push(str, tmp);
		i++;
	}
	free(line);
}
