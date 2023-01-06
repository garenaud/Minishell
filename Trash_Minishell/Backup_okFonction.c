//Fonction OK mais a ameliorer, backup au cas ou je casse tout...

int	pipe_exec(t_parser *p, t_exe *curr)
{
	int	prev_pipe;
	int	i;
	int	y;
	int	size;
	char	*path;

	i = 0;
	size = size_stack(p->struct_cmd.cmd);
	y = size_stack(p->struct_cmd.cmd) - 1;
	prev_pipe = STDIN_FILENO;
	while(i < size - 1)
	{
		pipe(curr->pfd);
		curr->pid = fork();
		path = getitem(p->struct_cmd.cmd, y);
		//printf("\nla commande est: %s et le chemin est: %s\n", curr->cmd_tab[0], path);
		if(curr->pid == 0)
		{
			if (prev_pipe != STDIN_FILENO)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			dup2(curr->pfd[1], STDOUT_FILENO);
			//printf("je suis dans l'enfant pipe exe et mon pid est: %d", curr->pid);
			close(curr->pfd[1]);
			execve(path, curr->cmd_tab p->env);
			perror("execve failed pipe");
			exit(1);
		}
		close(prev_pipe);
		close(curr->pfd[1]);
		prev_pipe = curr->pfd[0];
		curr = curr->next;
		i++;
		y--;
	}
	if (prev_pipe != STDIN_FILENO)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	//printll_exe(p->cmd_exe);
	path = getitem(p->struct_cmd.cmd, y);
	//printf("\nla commande est: %s et le chemin est: %s\n", curr->cmd_tab[0], path);
	execve(path, curr->cmd_tab, p->env);
		perror("execve failed last command");
	//printf("\nPID derniere commande = %d", curr->pid);
	close(prev_pipe);
	close(curr->pfd[1]);
	do_waits(p);
	printf("avant wait \n");
	printf("avant le dernier execve");
	return(1);
}

int	exec_bultout(t_parser *p, t_exe *curr)
{
	char	*path;
	char	*cmd;
	int		pos_path;
	int		i;
	
	i = 0;	
	while (p->struct_cmd.cmd)
	{
		cmd = curr->cmd_tab[0];
		pos_path = getpos(p->struct_cmd.cmd, cmd);
		path = getitem(p->struct_cmd.cmd, 0);
		//free(cmd);
		if_path_not_exist(curr, curr->cmd_tab, p->env);
		if (!access(path, X_OK))
		{
			printf("\nAVANT EXECVE, path = %s cmd = %s\n", path, cmd);
			if (execve(path, curr->cmd_tab, p->env) == -1)
			{
				i++;
				//free(path);
				ret(NULL, 127, 2);
			}
		}
		//free (path);
	}
	//delete(&p->struct_cmd.cmd);
	i = return1(i);
	return (0);
}

int	exec_bultout(t_parser *p, t_exe *curr)
{
	char	*path;
	int		i;
	int		y;
	
	i = 0;	
	y = 0;
	while (p->struct_cmd.cmd)
	{
		path = getitem(p->struct_cmd.cmd, y);
		//free(cmd);
		//if_path_not_exist(curr, curr->cmd_tab, p->env);
		if (!access(path, X_OK))
		{
			printf("\nAVANT EXECVE, path = %s cmd = %s\n", path, curr->cmd_tab[0]);
			if (execve(path, curr->cmd_tab, p->env) == -1)
			{
				i++;
				free(path);
				ret(NULL, 127, 2);
			}
		}
		p->struct_cmd.cmd = p->struct_cmd.cmd->next;
		curr = curr->next;
		y++;
		free (path);
	}
	//delete(&p->struct_cmd.cmd);
	i = return1(i);
	return (0);
}

/* void	execution(t_pars *pars, t_node *env)
{
	char	**tmp;
	char	**tmp_env;

	tmp_env = env_to_tab(env);
	tmp = conv_path(pars, env);
	if_path_not_exist(pars, tmp, tmp_env);
	if (tmp == NULL || exec_bultout_2(pars, tmp, tmp_env) == -1)
	{
		ret(pars->cmd, 127, 1);
		free_lst_pars(pars);
		free_lst_node(env);
	}
	if (tmp != NULL)
		free_tab(tmp);
	if (tmp_env != NULL)
		free(tmp_env);
} 

/* void	init_pipe(t_exe *curr)
{
	int		fd[10][2];
	int		i;

	i = 0;
	curr->fd_in = 0;
	while (i < 10)
	{
		pipe(fd[i]);
		printf("\nfd[%d][0]= %d,fd[%d][1]= %d \n", i,fd[i][0],i, fd[i][1]);
		i++;
	}
	i = 0;
	while (curr->next != NULL)
	{
		//pipe(fd);
		curr->fd_out = fd[i][1];
		printf("\nfd_out = %d\n", fd[i][1]);
		curr->next->fd_in = fd[i][0];
		printf("\nfd_in = %d\n", fd[i][0]);
		curr = curr->next;
		i++;
	}
	curr->fd_out = 1;
} */

int	cmd(t_pars *pars, t_node *env, t_prompt *prompt)
{
	signal(SIGINT, handle_sigquit);
	signal(SIGQUIT, handle_sigquit);
	redirection_tab(pars);
	init_cmd(pars);
	if (is_bultin(pars) != -1 && pars->next == NULL && pars->chevr == 0)
		bultin_search(pars, env, prompt);
	else
		pipeline(pars, env, prompt);
	return (0);
}*/


char	*set_and_get(t_parser *p)
{
	char	*inpt;

	inpt = NULL;
	p->piped = 0;
	//path_update(p);
	if (g_status > 4)
		p->return_val = g_status;
	g_status = WAITING;
	signal(SIGQUIT, SIG_IGN);
	inpt = readline(p->display_path);
	g_status = PARSING;
	if (inpt && ft_isprint(inpt[0]))
		add_history(inpt);
	return (inpt);
}


int	pipeline(t_parser *p, t_exe *curr)
{
	while (curr)
	{
		curr->pid = fork();
		printf("\ncurr->PID = %d", curr->pid);
		//printll_exe(curr);
		if (curr->pid == 0)
		{
			printf("Je suis le processus enfant (PID %d) (fd_out %d) (fd_in %d)\n", getpid(), curr->fd_out, curr->fd_in);
			if (curr->fd_out > 2)
				dup2(curr->fd_out, STDOUT_FILENO);
			if (curr->fd_in > 2)
				dup2(curr->fd_in, STDIN_FILENO);
			close_pipe2(curr);
			if (is_builtin(curr->cmd_tab) == -1)
				execution(p, curr);
			exit (127);
		}
		curr = curr->next;
	}
	printll_exe(curr);
	printf(YEL);
	printf("\non close les pipes");
	close_pipe2(curr);
	printf("\non wait les pipes");
	wait_pipe(curr);
	printf("\non a fini de wait\n");
	printf(ENDC);
	return (0);
}

void	execution(t_parser *p, t_exe *curr)
{
	if_path_not_exist(curr, curr->cmd_tab, p->env);
	if (curr->cmd_tab == NULL || exec_bultout(p, curr) == -1)
	{
		ret(curr->cmd_tab[0], 127, 1);
	}
	if (curr->cmd_tab != NULL)
		free_tab(curr->cmd_tab);
}

void	close_pipe2(t_exe *curr)
{
	while (curr != NULL)
	{
		if (curr->fd_in > 2)
		{
			close(curr->fd_in);
			printf("je close le FD_IN");
		}
		if (curr->fd_out > 2)
		{
			close(curr->fd_out);
			printf("je close le FD_IN");
		}
		else
			printf("\nPas de close\n");
		curr = curr->next;
	}
}
void	wait_pipe(t_exe *curr)
{
	while (curr != NULL)
	{
		if (curr->pid > 0)
		{
			wait(&g_status);
			if (WIFSIGNALED(g_status))
				g_status = 128 + g_status;
			if (WIFEXITED(g_status))
				g_status = WEXITSTATUS(g_status);
		}
		curr = curr->next;
	}
}

int	run_shell(t_parser *p)
{
	t_exe	*curr;

	curr = p->cmd_exe;
	if (p->piped)
	{
		if (pipe_loop(p, curr))
		{
			free_all(p);
			return(0);
		}
	}
	else if (inpt_checker(p, curr))
		return(0);
	return(1);
}

int	pipe_loop(t_parser *p, t_exe *curr)
{
	init_pipes(p);
	printf("\n\n\n print de curr au debut de pipe_loop ");
	printll_exe(curr);
	while (curr)
	{
		if (curr->fd_in < 0 || curr->fd_out < 0)
		{
			curr = curr->next;
			continue ;
		}
		curr->pid = fork();
		printf("\n\n%d: Cette phrase s'affiche dans les 2 processus\n", curr->pid);
		printf("\n\nPRINT AFTER FORK = %d", curr->pid);
		if (curr->pid == 0)
			child_pro(p, curr);
		curr = curr->next;
	}
	printf("\n\n\n print de cmd_exe apres pipe_loop ");
	printll_exe(p->cmd_exe);
	do_waits(p);
	//free_cmds(p);
	return (0);
}

int	child_pro(t_parser *p, t_exe *curr)
{
	int	old_stdin;
	int	old_stdout;

	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	if (curr->fd_in > 2)
		dup2(curr->fd_in, STDIN_FILENO);
	if (curr->fd_out > 2)
		dup2(curr->fd_out, STDOUT_FILENO);
	close_pipes(curr);
	inpt_checker(p, curr);
	exit(0);
}

void	close_pipes(t_exe *curr)
{
	while (curr != NULL)
	{
		if (curr->fd_in > 2)
			close(curr->fd_in);
		if (curr->fd_out > 2)
			close(curr->fd_out);
		curr = curr->next;
	}
}

int	inpt_checker(t_parser *p, t_exe *curr)
{
	int	i;

	i = 0;
	if (is_builtin(curr->cmd_tab))
	{
		printf("builtin, ca sera bientot la\n\n");
		return (1);
	}
	else
		if (is_function(p, curr))
			return (1);
	return (0);
}

/* int	pipe_checker(t_parser *p)
{
	int	i;

	i = 0;
	while (p->cmd_exe->cmd_tab)
	{
		if (p->cmd_exe->cmd_tab[0][0] == '|')
		{
			ft_putstr_fd("error near unexpected token\n", STDERR_FILENO);
			return (1);
		}
		if (ft_pipetok(p->cmd_exe->cmd_tab[i][0]))
		{
			if (!p->cmd_exe->cmd_tab[i + 1] || ft_pipetok(p->cmd_exe->cmd_tab[i + 1][0]))
			{
				ft_putstr_fd("error near unexpected token\n", STDERR_FILENO);
				return (1);
			}
		}
		i++;
	}
	return (0);
} */

/* int	redirection_tab(t_exe *curr)
{
	int		i;

	while (curr != NULL)
	{
		curr->chevr = 0;
		i = 0;
		while (curr->cmd_tab[i])
		{
			if (chevron_detect(curr, curr->cmd_tab[i], i) == -1)
				i++;
			else
				curr->chevr++;
		}
		curr = curr->next;
	}
	return (0);
} */

/* int	pipe_exec(t_parser *p, t_exe *curr)
{
	int	prev_pipe;
	int	i;
	int	y;
	int	size;
	char	*path;

	i = 0;
	size = size_stack(p->struct_cmd.cmd);
	y = size_stack(p->struct_cmd.cmd) - 1;
	prev_pipe = STDIN_FILENO;
	while(i < size - 1)
	{
		pipe(curr->pfd);
		curr->pid = fork();
		path = getitem(p->struct_cmd.cmd, y);
		//printf("\nla commande est: %s et le chemin est: %s\n", curr->cmd_tab[0], path);
		if(curr->pid == 0)
		{
			if (prev_pipe != STDIN_FILENO)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			dup2(curr->pfd[1], STDOUT_FILENO);
			//printf("je suis dans l'enfant pipe exe et mon pid est: %d", curr->pid);
			close(curr->pfd[1]);
			execve(path, curr->cmd_tab p->env);
			perror("execve failed pipe");
			exit(1);
		}
		close(prev_pipe);
		close(curr->pfd[1]);
		prev_pipe = curr->pfd[0];
		curr = curr->next;
		i++;
		y--;
	}
	if (prev_pipe != STDIN_FILENO)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	//printll_exe(p->cmd_exe);
	path = getitem(p->struct_cmd.cmd, y);
	//printf("\nla commande est: %s et le chemin est: %s\n", curr->cmd_tab[0], path);
	execve(path, curr->cmd_tab, p->env);
		perror("execve failed last command");
	//printf("\nPID derniere commande = %d", curr->pid);
	close(prev_pipe);
	close(curr->pfd[1]);
	do_waits(p);
	printf("avant wait \n");
	printf("avant le dernier execve");
	return(1);
} */
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


/* void	exec(t_parser *p, char **env, t_env *env_l)
{
	t_exe	*current;

	current = p->cmd_exe;
	signal(SIGINT, handle_sigquit);
	signal(SIGQUIT, handle_sigquit);
	exec_with_pipe(p, envp, line, env);
	}
} */

int	ret(char *msg, int status, int num)
{
	g_status = status;
	if (num == 0)
	{
		if (msg != NULL)
			printf("%s\n", msg);
	}
	if (num == 1)
	{
		if (msg != NULL)
			printf("minishell: %s: command not found\n", msg);
	}
	g_status = 0;
	return (0);
}

void	init_pipe(t_exe *curr)
{
	curr->fd_in = 0;
	while (curr->next != NULL)
	{
		pipe(curr->pfd);
		curr->fd_out = curr->pfd[1];
		curr->next->fd_in = curr->pfd[0];
		curr = curr->next;
	}
	curr->fd_out = 1;
}



void	init_pipes(t_parser *p)
{
	t_exe	*tmp;
	int		fd[2];

	tmp = p->cmd_exe;
	printll_exe(p->cmd_exe);
	printf("\n\n\n print de curr ");
	printll_exe(tmp);
	while (tmp)
	{
		pipe(fd);
		if (!tmp->fd_out)
			tmp->fd_out = fd[1];
		else
			close(fd[1]);
		tmp = tmp->next;
		if (tmp != NULL && !tmp->fd_in)
			tmp->fd_in = fd[0];
		else
			close(fd[0]);
	}
	printf("\n\n\n print de curr apres init pipes ");
	printll_exe(tmp);
	printf("\n\n\n print de cmd_exe apres init pipes ");
	printll_exe(p->cmd_exe);
	//if (!curr->fd_out)
		//curr->fd_out = 1;
}