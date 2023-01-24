/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:33:42 by grenaud-          #+#    #+#             */
/*   Updated: 2023/01/24 10:29:59 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED		"\033[1m\033[31m"
# define GREEN		"\033[1m\033[32m"
# define YEL		"\033[0;33m"
# define PURP		"\033[0;35m"
# define ENDC		"\033[0m"
# define BOLDRED	"\033[31m"
# define BLUE		"\033[1;34m"
# define PIPE 124
# define WAITING 1
# define PARSING 2
# define WORKING 3
# define ERROR 4

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>

int	g_status;

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}	t_list;

typedef struct s_list_i
{
	int				data;
	struct s_list_i	*next;
}	t_list_i;

typedef struct s_dico
{
	char			*key;
	char			*value;
	struct s_dico	*next;
}	t_dico;

// structure "dico"
// version stack
typedef struct s_util
{
	int			flag;
	int			position;
	int			pos1;
	int			pos;
	int			i1;
	int			i2;
	char		*c_tmp;
	char		*c_tmp1;
	char		*key;
	int			code_nb;
	t_list		*tmp;
	t_list		*delim;
	t_list		*raw;
	t_list		*raw_tmp;
	t_list		*sq;
	t_list		*dq;
	t_list		*dollar;
	t_list		*key_l;
	t_list		*del;
	t_list_i	*code;
}	t_util;

typedef struct s_built
{
	int			i;
	int			exception;
	char		*key;
	char		*value;
	t_dico		*tmp;
	t_list		*key_l;
	t_list		*value_l;
	t_list		*arg;
}	t_built;

//struct list pour execve
typedef struct s_exe
{
	char			**cmd_tab;
	char			*path;
	int				redir;
	int				fd_in;
	int				fd_out;
	pid_t			pid;
	int				pfd[2];
	struct s_exe	*next;
}	t_exe;

typedef struct s_env {
	char			*str;
	char			*name;
	char			*value;
	int				valid;
	int				order;
	struct s_env	*next;
}				t_env;

// structure "dico"
// version stack

typedef struct s_path
{
	char	*path;
	t_list	*path_raw;
	t_list	*split_path;
	t_list	*env_list;
}	t_path;

typedef struct s_cmd
{
	t_list			*cmd;
	t_list			*option;
	t_list			*arg;
	char			**tab_cmd;
	struct s_path	*path;
}	t_cmd;

typedef struct s_file
{
	t_list			*file;
	t_list			*fd;
	t_list			*rwx;
	int				nb_cmd;
	int				redir_status;
	pid_t			pid;
	t_cmd			*cmd;
}	t_file;

typedef struct s_parser
{
	t_list_i		*word_len;
	t_list_i		*flag;
	t_built			built;
	t_dico			*dico;
	t_dico			*dico_tmp;
	t_dico			*check;
	t_dico			*cmd_d_tmp;
	t_dico			*cmd_d;
	t_dico			*cmd_copy;
	t_dico			*envvar;
	t_util			util;
	t_list			*raw;
	t_list			*word;
	t_exe			*cmd_exe;
	t_list_i		*dquote;
	t_list_i		*squote;
	t_list_i		*pipe_i;
	t_list_i		*to_out_i;
	t_list_i		*to_in_i;
	t_list_i		*append_i;
	t_list_i		*heredoc_i;
	t_dico			*cmd_line;
	char			*display_path;
	char			*line;
	char			*tmp;
	char			**env;
	t_env			*env_l;
	int				empty;
	int				piped;
	int				redir;
	struct termios	*signal;
	int				return_val;
	t_path			struct_path;
	t_cmd			struct_cmd;
	t_file			struct_file;
	t_exe			struct_exe;
}	t_parser;

// la libft
size_t		ft_strlen(const char *str);
size_t		ft_strlen_c(const char *str, char del);
char		*ft_strdup(char *src);
char		*ft_strcpy(char *dest, const char *src);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isalnum(int c);
int			ft_isnum(char c, int pos);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
void		ft_putnbr_fd(int n, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_strtolower(char *str);
int			ft_isprint(int c);
char		*ft_itoa(int nb);

// integer stack

void		push_int(t_list_i **top, int item);
int			pop_int(t_list_i **top);
void		delete_int(t_list_i **top);
t_list_i	*reverse_int(t_list_i **top);
size_t		size_stack_int(t_list_i *top);
void		printll_int(t_list_i *lst);
int			remove_position_int(t_list_i **top, size_t pos);
int			getitem_int(t_list_i *top, size_t pos);
// string stack (basic)
void		push(t_list **top, char *item);
char		*pop(t_list **top);
void		delete(t_list **top);
t_list		*reverse(t_list **top);
size_t		size_stack(t_list *top);
void		printll(t_list *lst);

// string stack
int			transfer_c(t_list **start, t_list **end);
char		*getitem_c(t_list *top, size_t pos);
char		*getitem(t_list *top, size_t pos); // doublon
int			remove_pos_c(t_list **top, size_t pos);
int			getpos_c(t_list *top, char *item);

// parsing
void		trim_list(t_list **str);
char		*delimitateur(t_list **raw);
char		*getword1(t_list **raw, char *search);
char		*getall(t_list **raw);
void		create_raw_list(t_list **str, char *line);
void		create_raw_list_and_free(t_list **str, char *line);
void		create_quote_list(t_list **str, t_list_i **pos, char *search);
void		inclusion(t_list_i **sq, t_list_i **dq, int s_index, int d_index);
char		*getpath(t_list **raw);
// init parsing
void		init_pgrm_list_i(t_parser *p);
void		init_pgrm_list_c(t_parser *p);
void		init_pgrm_dico(t_parser *p);
void		init_pgrm_file(t_parser *p);
void		init_pgrm_cmd(t_parser *p);
void		init_built(t_parser *p);
void		init_parsing_list(t_parser *p);
void		init_parsing_list_c(t_parser *p);
void		delete_parsing_list_c(t_parser *p);
void		create_delim(t_parser *p);
void		init_mini(t_parser *p, char **env);
void		reload(t_parser *p, char **env);
void		parse_it(t_parser *p);
// memory cleaning
void		clean_memory_end(t_parser *p);
void		clean_memory_parsing(t_parser *p);

// signal
void		sig_handler(int signum);
int			readline_manager(t_parser *p);

// utilitaire
void		init_pgrm(t_parser *p, char *env[]);
void		init_pgrm_list_c(t_parser *p);
void		init_pgrm_list_i(t_parser *p);
void		init_pgrm_dico(t_parser *p);
void		init_pgrm_file(t_parser *p);
void		init_pgrm_cmd(t_parser *p);
void		free_parsing(t_parser *p);
void		init_util(t_parser *p);
void		init_struct_path(t_parser *p);

// dico

void		push_dico(t_dico **top, char *key, char *value);
t_dico		*pop_dico(t_dico **top);
void		delete_dico(t_dico **top);
size_t		size_stack_dico(t_dico *top);
int			get_key(t_dico *top, char *item);
int			get_value(t_dico *top, char *item);
int			remove_pos_dico(t_dico **top, size_t pos);
int			transfer_dico(t_dico **start, t_dico **end);
t_dico		*reverse_dico(t_dico **top);
t_dico		*getitem_dico(t_dico *top, size_t pos);
void		create_dico_list(t_dico **dico, char *env[]);
void		printll_dico(t_dico *dico);
size_t		find_min_key(t_dico *dico);
size_t		find_max_key(t_dico *dico);
void		tri_export(t_parser *p);
void		duplicate(t_dico **orig, t_dico **copy);

void		create_path_access(t_parser *p);
void		init_parsing_list_c(t_parser *p);
void		check_quote_1(t_parser *p);
void		delete_parsing_list_c(t_parser *p);

// env + path
char		*path_list(char *env[]);
void		create_path_access(t_parser *p);
void		get_path(t_parser *p);
void		cpd1_key(t_parser *p);

// test
void		check_quote_1(t_parser *p);
void		check_quote_3(t_parser *p);
void		print_ic(t_list_i *lst_i, t_list *lst);
void		get_inside_space(t_parser *p);
void		clean_dico(t_parser *p);
void		create_parsing_dict(t_parser *p);

// token a verifier tsc transfer successive c
int			get_code_c(t_parser *p, char c);
int			get_code_s(char *s);
int			code1(t_parser *p, char *c);
void		transfer_2c_space(t_parser *p, char *s);
int			transfer_normal_char(t_parser *p);
void		transfer_normal_char1(t_parser *p);
int			tsc(t_list **start, t_list **end, char c);
int			c_s_c(t_parser *p, char *c);
void		transfer_char_space(t_parser *p);
void		expand_to_value(t_parser *p);
void		get_inside_dquote2(t_parser *p);
void		get_inside_squote2(t_parser *p);
void		get_inside_space1(t_parser *p);
///void		transfer_normal_char11(t_parser **p);
void		tester(t_parser *p);
void		init_helper(t_parser *p);
void		get_inside_dq(t_parser *p, int pos1);
void		transfer_helper_1(t_parser *p, int code);
void		transfer_normal_char_helper1(t_parser *p, int code);

//execution
int		init_exe(t_parser *p);
t_exe	*init_exe_list(int size);
void	delete_exeline(t_exe **top);
void	free_tab(char **tab);
void	printll_exe(t_exe *exec);
int		checknb_arg(t_dico *top, t_parser *p);
int		checknb_pipe(t_dico *top);
size_t	size_stack_exe(t_exe *top);
int		free_all(t_parser *p);
char	*get_pos_path(t_parser *p, char *cmd);
void 	free_exe_list(t_exe *list);
void	fill_exec(t_parser *p, t_exe *curr, int size);
int		is_function(char *path, char **str, t_parser *p);
int		inpt_checker(char *path, char **str, t_parser *p);
void	close_pipes(t_exe *curr);
int		child_pro(t_parser *p, t_exe *curr);
int		pipe_loop(t_parser *p, t_exe *curr);
int		run_shell(t_parser *p);
void	waits(t_parser *p);
void	free_cmds(t_parser	*p);
void	do_wait(t_parser *p);
void	init_pipes(t_exe *curr);
int		if_path_not_exist(t_exe *curr, char **path_tab, char **env);
int		execute(char **str, t_parser *p);
char	*init_path(t_parser *p, char **cmd);



//redirection
int			is_redir(char *key);
int			redir(t_parser *p, t_dico *cmd_d, t_exe *curr);
int			output(t_parser *p, t_dico *cmd_d, t_exe *curr);
int			input(t_parser *p, t_dico *cmd_d, t_exe *curr);
int			append(t_parser *p, t_dico *cmd_d, t_exe *curr);
void		own_heredocs_to_long(char *delimiter, char *line, int *fd, t_exe *curr);
int			own_heredocs(t_parser *p, t_dico *cmd_d, t_exe *curr);
int			checknb_arg_calloc(t_dico *top);
int			checknb_redir(t_dico *top);


//signal
void		handle_sigint(int sig);
void		handle_signal(struct termios *saved);
void		hide_key(struct termios *saved);
void		handle_sigquit(int sig);
void		handle_sigquit(int signum);

int			set_signal(void);
void		setup_term(struct termios *show);
void		handle_signals(int signo);
char		*set_and_get(t_parser *p);
int			exit_checker(char **str, t_parser *p);
void		exit_free(t_parser *p, char **str);
void		exit_free_1(t_parser *p, char **str, int exit_code);


//builtin
void		init_built(t_parser *p);
int			bultin_search(t_exe *curr, t_parser *p);
int			is_builtin(char **str);
int			bultin_echo(int i, t_exe *curr);
int			bultin_echo_n(t_exe *curr);
int			bultin_cd(t_exe *curr, t_parser *p);
int			bultin_env(t_exe *curr, t_parser *p);
int			bultin_unset(t_exe *curr, t_parser *p);
int			bultin_pwd(void);
int			bultin_export(t_exe *curr, t_parser *p);

void	print_banner(void);

#endif
