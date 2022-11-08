/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:33:42 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/08 15:08:24 by jsollett         ###   ########.fr       */
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
	//int		a;
	char	*data;
	struct s_list	*next;
}	t_list;

typedef struct s_list_i
{
	int		data;
	struct s_list_i	*next;
}	t_list_i;

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

size_t		ft_strlen(const char *str);
size_t		ft_strlen_c(const char *str, char del);
char		*ft_strdup(char *src, int free_it);
char		*ft_strcpy(char *dest, const char *src);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		push(t_list **top, char	 *item);
void		push_int(t_list_i **top, int item);
char		*pop(t_list **top);
int			pop_int(t_list_i **top);
void		delete(t_list **top);
void		delete_int(t_list_i **top);
t_list		*reverse(t_list **top);
t_list_i	*reverse_int(t_list_i **top);
void		printll(t_list *lst);
void		printll_int(t_list_i *lst);
void		print_adr(t_list *lst);
size_t		size_stack(t_list *top);
size_t		size_stack_int(t_list_i *top);
int			remove_position(t_list **top, size_t pos);
int			remove_position_int(t_list_i **top, size_t pos);
char		*getitem(t_list *top, size_t pos);
int			getitem_int(t_list_i *top, size_t pos);
void		trim_list(t_list **str);
char		*trim(char *line);
int			getposition(t_list *top, char *item);
int			getposition_int(t_list_i *top, int item);
char		*delimitateur(t_list **raw);
char		*getword(t_list **raw, char *search);
char		*getword1(t_list **raw, /* t_list_i *sq, t_list_i *dq, */ char *search);
void		create_raw_list(t_list **str, char *line);
void		create_quote_list(t_list **str, t_list_i **pos, char *search);
void		inclusion(t_list_i **sq, t_list_i **dq, int s_index, int d_index);
void	    sig_handler(int signum);
void		init_pgrm(t_parser *p, char *env[]);
void    	free_parsing(t_parser *p);


#endif