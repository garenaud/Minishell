/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:42:43 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/22 17:20:51 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	run_shell(t_parser *p, char **args, char *inpt)
{
	if (p->piped)
	{
		if (!pipe_checker(args))
		{
			if (pipe_loop(args, p))
			{
				free_all(args, inpt, p->escape);
				return (0);
			}
		}
	}
	else if (inpt_checker(args, p))
		exit_free(p, args);
	free_all(args, NULL, p->escape);
	return (1);
}

int	pipe_loop(char **str, t_parser *p)
{
	t_cmd	*curr;

	fill_tab(str, p);
	curr = p->cmd_exe;
	init_pipes(p);
	while (curr)
	{
		if (curr->fd_in < 0 || curr->fd_out < 0)
		{
			curr = curr->next;
			continue ;
		}
		curr->pid = fork();
		if (curr->pid == 0)
			child_pro(p, curr);
		curr = curr->next;
	}
	do_waits(p);
	free_cmds(p);
	return (0);
}

int	child_pro(t_parser *p, t_cmd *curr)
{
	int	old_stdin;
	int	old_stdout;

	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	if (curr->fd_in > 2)
		dup2(curr->fd_in, STDIN_FILENO);
	if (curr->fd_out > 2)
		dup2(curr->fd_out, STDOUT_FILENO);
	close_pipes(p->cmd_exe);
	inpt_checker(curr->cmd_tab, p);
	exit(0);
}

static void	close_pipes(t_cmd *curr)
{
	while (curr)
	{
		if (curr->fd_in > 2)
			close(curr->fd_in);
		if (curr->fd_out > 2)
			close(curr->fd_out);
		curr = curr->next;
	}
}

int	inpt_checker(char **str, t_parser *p)
{
	int	i;

	i = 0;
	if (!(str))
		return (0);
	if (is_builtin(str))
	{
		if (inpt_checker_1(str, p))
			return (1);
	}
	else
		if (is_function(str, p))
			return (1);
	return (0);
}

int	is_function(char **str, t_parser *p)
{
	pid_t	childpid;

	childpid = fork();
	if (childpid == 0)
	{
		is_function_2(str, p);
		exit (127);
	}
	else
		waitpid(childpid, &(p->return_val), 0);
	if (WIFEXITED(p->return_val))
		p->return_val = WEXITSTATUS(p->return_val);
	return (0);
}

static void	do_waits(t_parser *p)
{
	t_cmd	*curr;

	curr = p->cmd_exe;
	close_pipes(curr);
	while (curr)
	{
		waitpid(curr->pid, &p->return_val, 0);
		curr = curr->next;
	}
}

int	pipe_checker(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0][0] == '|')
		{
			ft_putstr_fd("error near unexpected token\n", STDERR_FILENO);
			return (1);
		}
		if (ft_pipetok(str[i][0]))
		{
			if (!str[i + 1] || ft_pipetok(str[i + 1][0]))
			{
				ft_putstr_fd("error near unexpected token\n", STDERR_FILENO);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_pipetok(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}