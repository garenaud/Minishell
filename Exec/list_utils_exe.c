/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_exe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:45:54 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/23 12:43:18 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exe	*init_exe_list(int size)
{
	t_exe	*new;
	
	new = (t_exe *)malloc(sizeof(t_exe));
	if (!new)
		return(NULL);
	new->pid = 0;
	new->cmd_tab = calloc(size + 1, sizeof(char *));
	new->fd_in = 0;
	new->fd_out = 0;
	new->next = NULL;
	return (new);
}

void	printll_exe(t_exe *exec)
{
	printf(GREEN "start exe");
	int	i;
	i = 0;
	while (exec != NULL)
	{
		printf("-->fd_in[%d] fd_out[%d] pid[%d]\n", exec->fd_in, exec->fd_out, exec->pid);
		while (exec->cmd_tab[i])
		{
			printf("cmd_tab[%i]=[%s]-->", i, exec->cmd_tab[i]);
			i++;
		}
		i = 0;
		printf(" fin de l'element' \n\n");
		exec = exec->next;
	}
	printf("-->[end]\n"ENDC);
}

size_t	size_stack_exe(t_exe *top)
{
	size_t	size;

	size = 0;
	while (top != NULL)
	{
		size++;
		top = (top)->next;
	}
	return (size);
}

void delete_exeline(t_exe **top)
{
    t_exe *current;
    t_exe *next;
	
	current = *top;
    while (current != NULL)
    {
        next = current->next;
        free_tab(current->cmd_tab);
        //free(current->cmd_tab);
        current = current->next;
    }
    free(current);
    *top = NULL;
}

void free_tab(char **tab)
{
    int i;

	i = 0;
    if (tab == NULL)
        return;
    while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	//free(tab[i]);
    free(tab);
}