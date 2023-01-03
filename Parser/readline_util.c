/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:37 by jsollett          #+#    #+#             */
/*   Updated: 2022/12/29 10:23:07 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int signum)
{//https://stackoverflow.com/questions/16828378/readline-get-a-new-prompt-on-sigint
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGABRT)
		signal(SIGABRT, SIG_IGN);
}

int	readline_manager(t_parser *p)
{
	signal(SIGINT, sig_handler);
	if (ft_strncmp(p->line, "quit", 4) == 0)
	{
		free_parsing(p);
		return (1);
	}
	if (ft_strncmp(p->line, "", 1) == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (ft_strncmp(p->line, "clear", 5) == 0)
		rl_clear_history();
	if (ft_strlen(p->line) > 0)
		add_history(p->line);
	return (0);
}

/* int	prompt_(t_parser *p, t_prompt *prompt)
{
	t_pars	*tmp;

	prompt->user = username(head);
	prompt->buffer = readline(prompt->user);
	exit_ctrld(prompt, pars);
	if (prompt->buffer != NULL && prompt->buffer[0] != '\0')
		add_history(prompt->buffer);
	if (prompt->buffer != NULL && prompt->buffer[0] != '\0'
		&& is_tab(prompt->buffer) != -1 && check_chev(prompt->buffer) != -1)
	{
		if (data_to_lst(&pars, prompt->buffer) == -1)
		{
			free (prompt->buffer);
			free (prompt->user);
			return (1);
		}
	}
	tmp = pars;
	lst_to_tab(tmp, head);
	init_pipe_cmd(head, pars, prompt);
	free_prompt(pars, prompt);
	return (0);
} */