/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:47:13 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/29 10:29:42 by grenaud-         ###   ########.fr       */
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
	return (-1);
}

int	is_function_2(t_parser *p, t_exe *curr)
{
 	char	*path;
	char	*cmd1;
	int		i;
	int		pos_path;
	
	printf("\n\nJE SUIS DANS LE IS_FUNCTION2\n");
	cmd1 = strdup(curr->cmd_tab[0]);
	printf("la cmd1 = %s\n", cmd1);
	pos_path = getpos(p->struct_cmd.cmd, cmd1);
	//path = strdup(getitem(p->struct_cmd.cmd, pos_path));
	printf("\nLA POSITION de PATH DE LA COMMANDE EST: %i\n", pos_path);
	//path = strdup(getitem(p->struct_cmd.cmd, getpos_c(p->struct_cmd.cmd, cmd1)));
	i = 0;
	printll_exe(curr);
	printf("\n\nles path: ");
	printll(p->struct_cmd.cmd);
	while (curr)
	{
		path = strdup(getitem(p->struct_cmd.cmd, 0));
		printf("\n\n\nLE PATH EST: %s\n\n\n", path);
		printf("juste avant execve le path est %s\n", path);
		remove_pos_c(&p->struct_cmd.cmd, 0);
		if (execve(path, curr->cmd_tab, p->env) == -1)
			i++;
		curr = curr->next;
		//path_list = p->struct_cmd.cmd->next;
		i++;
	}
	free(path);
	printf ("Error : %s\n", strerror(22));
	return (1); 
}

int	is_function(t_parser *p, t_exe *curr)
{
	pid_t	childpid;

	childpid = fork();
	printf("\nle childpid dans is_function %d\n", childpid);
	if (childpid == 0)
	{
		printf("\n J'ENTRE DANS LE CHILDPID\n");
		is_function_2(p, curr);
		exit (127);
	}
	else
		waitpid(childpid, &(p->return_val), 0);
	if (WIFEXITED(p->return_val))
		p->return_val = WEXITSTATUS(p->return_val);
	return (0);
}

/* void	wait_pipe(t_parser *p)
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
 */