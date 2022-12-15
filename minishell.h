/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:33:42 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/15 21:43:58 by grenaud-         ###   ########.fr       */
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <termios.h>

int	g_exit_status;

typedef struct s_list
{
	char	*data;
	struct s_list	*next;
}	t_list;

typedef struct s_list_i
{
	int		data;
	struct s_list_i	*next;
}	t_list_i;

//struct list pour execve
typedef struct s_exe
{
	char	**cmd_tab;
	int		fd_in;
	int		fd_out;
	int		pid;
	int		pfd[2];
	struct s_exe	*next;
}	t_exe;

// structure "dico"
// version stack
typedef struct s_dico
{
	char	*key;
	char	*value;
	struct s_dico	*next;
}	t_dico;

typedef struct s_path
{
	char	*path;
	t_list	*path_raw;
	t_list	*split_path;
	t_list	*env_list;
}	t_path;

typedef struct s_cmd
{
	t_list		*cmd;
	t_list		*option;
	t_list		*arg;
	char		**cmd_array;
	struct s_path	*path;
}	t_cmd;

typedef	struct s_file
{
	t_list			*file;
	t_list			*fd;
	t_list			*rwx;
	int				nb_cmd;
	int				redir_status;
	pid_t			pid;
	t_cmd			*cmd;
}	t_file;

typedef	struct s_stream
{
	t_list		*pipe;
	t_list		*to_out; // >
	t_list		*to_in; //<
	t_list		*append;  // >>
	t_list		*here_doc; // <<
}	t_stream;

typedef struct s_parser
{
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
	t_dico			*dico;
	t_dico			*dico_tmp;
	t_dico			*check;
	t_dico			*cmd_line;
	char   			*line;
	char			*tmp;
	char			**env;
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

// integer stack

void		push_int(t_list_i **top, int item);
int			pop_int(t_list_i **top);
void		delete_int(t_list_i **top);
t_list_i	*reverse_int(t_list_i **top);
size_t		size_stack_int(t_list_i *top);
void		printll_int(t_list_i *lst);
int			remove_position_int(t_list_i **top, size_t pos);
int			getitem_int(t_list_i *top, size_t pos);
int			getposition_int(t_list_i *top, int item);

// string stack (basic)
void		push(t_list **top, char	 *item);
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
int			remove_position(t_list **top, size_t pos);
int			getpos_c(t_list *top, char *item);
int			getposition(t_list *top, char *item);
void		print_adr(t_list *lst);

// parsing
void		trim_list(t_list **str);
//char		*trim(char *line);
char		*delimitateur(t_list **raw);
//char		*getword(t_list **raw, char *search);
char		*getword1(t_list **raw,  char *search);
void		create_raw_list(t_list **str, char *line);
void		create_quote_list(t_list **str, t_list_i **pos, char *search);
void		inclusion(t_list_i **sq, t_list_i **dq, int s_index, int d_index);
char		*getpath(t_list **raw);
void		init_parsing_list(t_parser *p);


// signal
void	    sig_handler(int signum);

// utilitaire
void		init_pgrm(t_parser *p, char *env[]);
void    	free_parsing(t_parser *p);

// test
char    	*path_list(char *env[]);
void    	create_env_list(t_list **env_list, char *env[]);
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
void		check_quote(t_parser *p);

void		create_path_access(t_list *path, t_parser *p);
void		init_parsing_list_c(t_parser *p);
void    	add_space(t_parser *p);
void		check_quote_1(t_parser *p);
void    	delete_parsing_list_c(t_parser *p);
t_dico		*getword_2(t_list **raw, char *search);
void		get_path(t_parser *p, char **env);

//execution
void	exec_pipe(t_parser *p, char *env[]);
void	execution(t_list *path, t_list *arg, char *env[]);
void	close_pipe(t_parser *p);
void	wait_pipe(t_parser *p);
void	init_pipe(t_parser *p);
void	init_exe(t_parser *p);
void	printll_exe(t_exe *cmd_exe);
t_exe	*init_exe_list(t_dico *cmd_line);
int		nb_arr(t_dico *cmd_line);
void	delete_exeline(t_exe **top);
void	free_tab(char **tab);

/* void	start_bins(t_cmd *current, t_env *env, char **envp, char **execute);
 */
//cmd init
char 	**list_to_array(t_dico *word);

//signal
void	handle_sigint(int sig);
void	handle_signal(struct termios *saved);
void	hide_key(struct termios *saved);
void	handle_sigquit(int sig);


#endif