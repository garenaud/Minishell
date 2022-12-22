/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:47:13 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/22 17:14:25 by grenaud-         ###   ########.fr       */
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
