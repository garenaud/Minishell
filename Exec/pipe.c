/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:47:13 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/13 18:33:41 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec(t_parser *p, char **envp, t_env *env)
{
	t_list	*current;

	current = p->word;
	signal(SIGINT, handle_sigquit);
	signal(SIGQUIT, handle_sigquit);
	if (current->next == NULL && (builtin(list, envp, line) != -1)
		&& (p->struct_file.redir_status != 1))
	{
		exec_builtin(current, list, line, env);
	}
	else
	{
		exec_with_pipe(list, envp, line, env);
	}
}

void	close_pipe(t_parser *p)
{
	t_list	*current;

	current = p->word;
	while (current != NULL)
	{
		if (p->struct_file.fd_in > 2)
			close(p->struct_file.fd_in);
		if (p->struct_file.fd_out > 2)
			close(p->struct_file.fd_out);
		current = current->next;
	}
}

void	wait_pipe(t_parser *p)
{
	t_list	*current;
	int		wstatus;

	current = p->word;
	while (current != NULL)
	{
		if (p->struct_file.pid > 0)
		{
			waitpid(p->struct_file.pid, &wstatus, 0);
			if (WIFEXITED(wstatus))
				g_exit_status = WEXITSTATUS(wstatus);
		}
		current = current->next;
	}
}

void	init_pipe(t_parser *p)
{
	int		fd[2];
	t_list	*current;
	current = p->word;
	p->struct_file.fd_in = 0;
	while (current != NULL)
	{
		pipe(fd);
		p->struct_file.fd_out = fd[1];
		p->struct_file.fd_in = fd[0];
		current = current->next;
	}
	p->struct_file.fd_out = 1;
	current = p->word;
	while(current)
	{
		current = current->next;
	}
	printll(current);
}

void	exec_pipe(t_parser *p, char *env[])
{
	t_list	*current;
	current = p->struct_path.path_raw;
	p->struct_file.pid = 0;
	while(current != NULL)
	{
		p->struct_file.pid = fork();
		if(p->struct_file.pid == 0)
		{
			if(p->struct_file.fd_out > 2)
				dup2(p->struct_file.fd_out, STDOUT_FILENO);
			if(p->struct_file.fd_in > 2)
				dup2(p->struct_file.fd_in, STDIN_FILENO);
			close_pipe(p);
			start_bins(current, arg, env);
			exit(127);
		}
		current = current->next;
	}
	close_pipe(p);
	wait_pipe(p);
}

void	bins_execute(char **split_path, char **envp, t_cmd *cmd)
{
	int		i;
	int		y;
	char	*tmp;
	char	*tmp2;

	i = 0;
	y = -1;
	tmp = NULL;
	tmp2 = NULL;
	while (split_path && split_path[++y])
	{
		tmp = ft_strjoin(split_path[y], "/");
		if (cmd->tab[0] != NULL)
			tmp2 = ft_strjoin(tmp, cmd->tab[0]);
		free (tmp);
		if (!access(tmp2, X_OK))
		{
			if (execve(tmp2, cmd->tab, envp) == -1)
				i++;
		}
		free(tmp2);
	}
	check_command_not_found(i, envp, cmd);
}

void	start_bins(t_cmd *current, t_env *env, char **envp, char **execute)
{
	execute = bins(current, env);
	bins_execute(execute, envp, current);
	if (execute != NULL)
		free_split_path(execute);
}