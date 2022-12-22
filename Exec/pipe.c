/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:47:13 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/22 23:13:27 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* void	exec(t_parser *p, char **env, t_env *env_l)
{
	t_exe	*current;

	current = p->cmd_exe;
	signal(SIGINT, handle_sigquit);
	signal(SIGQUIT, handle_sigquit);
	exec_with_pipe(p, envp, line, env);
	}
} */

int		is_builtin(char **str)
{
	if (str[0] == 0)
		return (0);
	if (!ft_strcmp(str[0], "echo") || !ft_strcmp(str[0], "pwd")
		|| !ft_strncmp(str[0], ".", 1) || !ft_strcmp(str[0], "env")
		|| !ft_strcmp(str[0], "exit") || !ft_strcmp(str[0], "cd")
		|| !ft_strcmp(str[0], "export") || !ft_strcmp(str[0], "unset")
		|| !ft_strncmp(str[0], "/", 1))
	{
		return (1);
	}
	return (0);
}

/*int	is_function_2(t_parser *p)
{
 	char	*path;
	int		i;
	t_exe	*curr;
	t_list	*path_list;
	
	curr = p->cmd_exe;
	path_list = p->struct_cmd->cmd;
	i = 0;
	while (curr)
	{
		path = strdup(path_list);
		if (execve(path, curr->cmd_tab, p->env) == -1)
			i++;
		curr = p->cmd_exe->next;
		path_list = p->struct_cmd->cmd->next;
		i++;
	}
	free(path);
	printf ("Error : %s\n", strerror(22));
	return (1); 
}*/

int	is_function(t_parser *p)
{
	pid_t	childpid;

	childpid = fork();
	if (childpid == 0)
	{
		//is_function_2(p);
		exit (127);
	}
	else
		waitpid(childpid, &(p->return_val), 0);
	if (WIFEXITED(p->return_val))
		p->return_val = WEXITSTATUS(p->return_val);
	return (0);
}

void	wait_pipe(t_parser *p)
{
	t_exe	*current;
	int		wstatus;

	current = p->cmd_exe;
	while (current != NULL)
	{
		if (p->struct_file.pid > 0)
		{
			waitpid(p->cmd_exe->pid, &wstatus, 0);
			if (WIFEXITED(wstatus))
				g_status = WEXITSTATUS(wstatus);
		}
		current = current->next;
	}
}
