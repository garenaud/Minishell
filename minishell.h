/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:33:42 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/15 13:11:26 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

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


// structure "dico"
// version stack

typedef struct s_dico
{
	char	*key;
	char	*value;
	struct s_dico	*next;
}	t_dico;

typedef struct s_parser
{
	t_list		*raw;
	t_list		*word;
	t_list_i	*dquote;
	t_list_i	*squote;
	char   		*line;
	char		*tmp;
	char		**env;
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




#endif