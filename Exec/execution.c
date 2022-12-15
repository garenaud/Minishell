/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:17:03 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/12 19:52:34 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
//#include "./minishell.h"

//fonction qui prepare la commande, check si c'est un builtin ou pas
/* void	execution(t_list *path, t_list *arg, char *env[])
{
	signal(SIGINT, handle_sigquit);
	signal(SIGQUIT, handle_sigquit);
	
	
} */

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
	int				fd_in;
	int				fd_out;
	pid_t			pid;
	t_cmd			*cmd;
}	t_file;

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		str++;
		count++;
	}
	return (count);
}

static	char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*dst;

	dst = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	ft_strcpy(dst, src);
	printf("<%p> strdup\n", dst);
	return (dst);
}

void	push(t_list **top, char	 *item)
{
	t_list	*tmp;
	
	printf("<%p>\n", *top);
	tmp = malloc(sizeof(t_list));
	if (!tmp)
		return;
	printf("<%p> push\n", tmp);
	tmp->data = ft_strdup(item);
	tmp->next = *top;
	*top = tmp; //?
}

void	printll(t_list *lst)
{
	printf("start");
	while (lst)
	{
		printf("-->[%s]", (lst->data));
		lst = lst->next;
	}
	printf("-->[end]\n");
}

int main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	pid_t	pid;
	t_file *file;
	t_list	**cmd;
	int		i;
	int		j;
/* 	cmd = malloc(sizeof(t_list));
 */	*cmd = NULL;
	i = 0;
	j = 0;
/* 	char **args[][4]= {{"/bin/ls","-allll", NULL},
    {"/usr/bin/grep", "mini", NULL},{"/usr/bin/wc", NULL} }; */
	char	*str;
	char	*str1 = "/bin/ls";
	char	*str2 = "-al";
	char	*str3 = NULL;
/* 	push(cmd, "a");
	push(cmd, "b");
	printll(*cmd); */
	printf("str1 = %s", str1);
	str = ft_strdup(str2);
	printf("str = %s", str);
	push(cmd, str1);
	return(0);
}