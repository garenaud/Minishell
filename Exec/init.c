/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 08:20:22 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/15 21:47:43 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* void	init_exe(t_parser *p)
{
	int	i;
	t_dico *curr;
	p->cmd_exe = init_exe_list();
	i = 0;
	curr = p->cmd_line;
	while(curr != NULL)
	{
		p->cmd_exe->cmd_tab[i] = malloc(sizeof(char *) * strlen(curr->value));
		push_exe(p->cmd_exe, curr->va)
		//p->cmd_exe->cmd_tab[i] = strdup(curr->value);
		i++;
		curr = curr->next;
		if (ft_strncmp(curr->value, "|", ft_strlen(curr->value)) == 0)
		{
			p->cmd_exe->cmd_tab[i] = NULL;
			i = 0;
			p->cmd_exe = p->cmd_exe->next;
			curr = curr->next;
		}
		else
			p->cmd_exe->cmd_tab[i] = NULL;
	}
} */

void	init_exe(t_parser *p)
{
	int	i;
	p->cmd_exe = init_exe_list(p->cmd_line);
	i = 0;
	while(p->cmd_line != NULL)
	{
		p->cmd_exe->cmd_tab[i] = ft_strdup(p->cmd_line->value);
		i++;
		p->cmd_line = p->cmd_line->next;
/* 		if (getitem_dico(p->cmd_line, i) = "|")
		{
			p->cmd_exe->cmd_tab[i] = NULL;
			i = 0;
			p->cmd_exe = p->cmd_exe->next;
			p->cmd_line = p->cmd_line->next;
		}*/
	}
	p->cmd_exe->cmd_tab[i] = NULL;
}

t_exe	*init_exe_list(t_dico *cmd_line)
{
	t_exe	*new;
	int		size;

	size = nb_arr(cmd_line);
	new = malloc(sizeof(t_exe));
	if (!new)
		return (0);
	new->next = NULL;
	new->pid = 0;
	new->cmd_tab = calloc(size, sizeof(char *));
	new->fd_in = 0;
	new->fd_out = 0;
	return (new);	
}

void	delete_exeline(t_exe **top)
{
	t_exe	*tmp;
	int		i;

	i = 0;
	if (*top == NULL)
		return;
	while (*top != NULL)
	{
	 	tmp = *top;
		*top = (*top)->next;
		//free(tmp->pid);
        //free(tmp->fd_in);
        //free(tmp->fd_out);
 		while(tmp)
		{
			free_tab(tmp->cmd_tab);
			free(tmp->cmd_tab);
			tmp->next;
		}
		//free(tmp);
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL || tab[0] == NULL)
		return ;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		++i;
	}
}
/* 
void	free_cmds(t_data	*data)
{
	t_exe	*curr;
	t_exe	*next;

	curr = data->pipe->h;
	data->pipe->err_out = 0;
	while (curr)
	{
		next = curr->next;
		if (curr->val)
		{
			free_tab(curr->val);
			free(curr->val);
		}
		free(curr);
		curr = next;
	}
}
 */
int		nb_arr(t_dico *cmd_line)
{
	int	i;
	
	i = 0;
	while (cmd_line != NULL)
	{
		i++;
		cmd_line = cmd_line->next;
	}
	return(i);
}

void	printll_exe(t_exe *cmd_exe)
{
	int	i;
	t_exe	*curr;
	curr = cmd_exe;
	i = 0;
	printf("start exec_init\n");
	while (curr != NULL)
	{
		while (curr->cmd_tab[i])
		{
			printf("cmd_tab[%i]=[%s]-->", i, curr->cmd_tab[i]);
			i++;
		}
		printf("\n");
		i = 0;
		curr = cmd_exe->next;
/* 		printf("-->[%s][%s]\n", (dico->key),(dico->value));
		dico = dico->next; */
	}
	printf("\n that's all folks\n");
}
/* 
char	**list_to_tab(t_parser *parser, t_dico *word) 
{
	int size;
	t_dico *current;
	int	i;
	int	j;
	current = word;
	file->tab_cmd = malloc(sizeof(char *) * ((file->nb_cmd) + 1));
	if (*tab_cmd == NULL)
		return(NULL);
	i = 0;
	j = 0;
	cmd_nb(file, word);
	while (current != NULL) 
	{
		file->tab_cmd[i] = malloc(sizeof(char *) * ((file->nb_arg) + 1))
		while (current != NULL)
		if (ft_strncmp(current->value, "|", ft_strlen(word->value)) != 0)
		{
			tab_cmd[i][j] = NULL;
			i++;
			j = 0;
			current = current->next;
		}
		tab_cmd[i][j] = current->value;
		j++;
		current = current->next;
  	}
 	i = 0;
	while (i < size)
	{
		printf("\ntab_cmd[%i] = %s", i, tab_cmd[i]);
		i++;
	}
 	return(tab_cmd);
}

void	cmd_nb(t_file *file, t_dico *word)
{
	int	i;
	i = 0;
	while (word != NULL)
	{
		if (ft_strncmp(word->value), "|", ft_strlen(word->value) == 0)
			i++;
		word->next;
	}
	file->nb_cmd = i;
	i = 0;
	while (ft_strncmp(word->value), "|", ft_strlen(word->value) != 0 || word != NULL)
	{
		i++;
		word->next;
	}
	file->nb_arg = i;
} */
/* memcpy(node->tab, tab, sizeof tab); */