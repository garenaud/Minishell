/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:09:44 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/24 14:38:41 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strtolower(char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
				str[i] += 32;
			i++;
		}
	}
}

int	is_builtin(char **str)
{
	ft_strtolower(str[0]);
	if (str[0] == 0)
		return (0);
	if (!ft_strcmp(str[0], "echo")
		|| !ft_strcmp(str[0], "pwd")
		|| !ft_strncmp(str[0], ".", 1)
		|| !ft_strcmp(str[0], "env")
		|| !ft_strcmp(str[0], "exit")
		|| !ft_strcmp(str[0], "cd")
		|| !ft_strcmp(str[0], "export")
		|| !ft_strcmp(str[0], "unset")
		|| !ft_strncmp(str[0], "/", 1))
	{
		return (1);
	}
	return (-1);
}

int	bultin_search(t_exe *curr, t_parser *p)
{
	ft_strtolower(curr->cmd_tab[0]);
	if (ft_strcmp(curr->cmd_tab[0], "echo") == 0)
		return (bultin_echo_n(curr));
	if (ft_strcmp(curr->cmd_tab[0], "cd") == 0)
		return (bultin_cd(curr, p));
	if (!ft_strncmp(curr->cmd_tab[0], "./", 1))
		if (execute(&curr->cmd_tab[0], p))
			return (1);
	if (!ft_strncmp(curr->cmd_tab[0], "/", 1))
		if (execute(&curr->cmd_tab[0], p))
			return (1);
	if (ft_strcmp(curr->cmd_tab[0], "pwd") == 0)
		return (bultin_pwd(p));
	if (ft_strcmp(curr->cmd_tab[0], "export") == 0)
		return (bultin_export(curr, p));
	if (ft_strcmp(curr->cmd_tab[0], "unset") == 0)
		return (bultin_unset(curr, p));
	if (ft_strcmp(curr->cmd_tab[0], "env") == 0)
		return (bultin_env(curr, p));
	if (ft_strcmp(curr->cmd_tab[0], "exit") == 0)
		if (exit_checker(curr->cmd_tab, p) == 1)
			exit_free(p, curr->cmd_tab);
	return (0);
}

int	exit_checker(char **str, t_parser *p)
{
	int	i;

	i = 0;
	if (str[1])
	{
		while (str[1][i])
		{
			if (!('0' <= str[1][i] && str[1][i] <= '9'))
				return (255);
			++i;
		}
	}
	i = 0;
	while (str[i])
		++i;
	if (i > 2)
	{
		p->return_val = 1;
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (0);
	}
	return (1);
}

void	exit_free(t_parser *p, char **str)
{
	int	exit_code;

	exit_code = 0;
	if (str[1])
	{
		exit_code = exit_checker(str, p);
		if (exit_code == 1)
		{
			ft_putstr_fd("exit\n", 2);
			exit_code = (atoi(str[1]));
		}
		else
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		}
	}
	else
		ft_putstr_fd("exit\n", 2);
/* 	if (p->cmd_exe != NULL)
		delete_exeline(&p->cmd_exe); */
	exit (exit_code);
}

void	exit_free_1(t_parser *p, char **str, int exit_code)
{
	//free(p->signal);
	free_tab(str);
	free(p->env);
	exit (exit_code);
}
