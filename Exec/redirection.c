/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:53:46 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/05 12:11:59 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir(t_dico *cmd_d, t_exe *curr)
{
	if (ft_strcmp(cmd_d->key, "3") == 0)
		output(cmd_d, curr);
	else if (ft_strcmp(cmd_d->key, "4") == 0)
		input(cmd_d, curr);		
}

int output(t_dico *cmd_d, t_exe *curr) 
{
	// Vérifiez que cmd_d et curr ne sont pas NULL
	if (cmd_d == NULL || curr == NULL) 
		return -1;
	// Ouvrez le fichier de destination de la redirection
	int fd = open(cmd_d->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1) 
	{
		perror("open: ");
		return -1;
	}
	// Fermez le fd actuel de sortie s'il est supérieur à 2
	if (curr->fd_out > 2)
		close(curr->fd_out);
	// Dupliquez le fd du fichier sur le fd standard de sortie (1)
	dup2(fd, 1);
	// Fermez le fd original du fichier
	close(fd);
	// Mettez à jour le fd de sortie courant
	curr->fd_out = fd;
	return 0;
}

int input(t_dico *cmd_d, t_exe *curr) 
{
	if (cmd_d == NULL || curr == NULL)
		return -1;
	int fd = open(cmd_d->next->value, O_RDONLY, 0644);
	if (fd == -1) 
	{
		perror("open: ");
		return(-1);
	}
	// Fermez le fd actuel d'entrée s'il est supérieur à 2
	if (curr->fd_in > 2)
    	close(curr->fd_in);
	// Dupliquez le fd du fichier sur le fd standard d'entrée (0)
	dup2(fd, 0);
	// Fermez le fd original du fichier
	close(fd);
	// Mettez à jour le fd d'entrée courant
	curr->fd_in = fd;
	return 0;
}


/* int	output(t_dico *cmd_d, t_exe *curr)
{
	int	fd;

	//printf("\ncurr->cmd_tab[%d] = %s", i, curr->cmd_tab[i + 1]);
	fd = open(cmd_d->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open: ");
		return (-1);
	}
	if (curr->fd_out > 2)
		close(curr->fd_out);
	curr->fd_out = fd;
	printf("\nle fd_out est = %d\n", curr->fd_out);
	return (0);
} */

/* int	input(t_dico *cmd_d, t_exe *curr)
{
	int	fd;

	fd = open(cmd_d->next->value, O_RDONLY, 0644);
	if (fd == -1)
	{
		perror("open: ");
		return (-1);
	}
	if (curr->fd_in > 2)
		close(curr->fd_in);
	curr->fd_in = fd;
	printf("\nle fd_in est = %d\n", curr->fd_in);
	return (0);
} */