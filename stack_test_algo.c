#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* #include "get_next_line.h"
 */
typedef struct s_list
{
	//int		a;
	char	*data;
	struct s_list	*next;
}	t_list;

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

size_t	ft_strlen_c(const char *str, char del)
{
	size_t	len;

	len = 0;
	while (*str != '\0' && *str != del)
	{
		str++;
		len++;
	}
	return (len);
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
//	printf("<%p> strdup\n", dst);
	return (dst);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (((n - 1) > 0) && (*s1 != '\0') && (*s2 != '\0') && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*s1 -(unsigned char)*s2);
}

void	push(t_list **top, char	 *item)
{
	t_list	*tmp;
	
//	printf("<%p>\n", *top);
	tmp = malloc(sizeof(t_list));
	if (!tmp)
		return;
//	printf("<%p> push\n", tmp);
	tmp->data = ft_strdup(item);
	tmp->next = *top;
	*top = tmp; //?
}

char	*pop(t_list **top)
{
	t_list	*tmp;
	char	*item;
	if (*top == NULL)
	{
		printf("Stack empty\n");
		//return (NULL);
		exit (0);
	}

	tmp = *top;
	item = ft_strdup(tmp->data);
	*top = (*top)->next;
//	printf("<%p> strdup pop\n",item);
//	printf("<%p> free pop -data\n", tmp->data);
	free(tmp->data);

//	printf("<%p> free pop -struct\n", tmp);
	free(tmp);
	return (item);
}

void	delete(t_list **top)
{
	t_list	*tmp;

	if (*top == NULL)
		return;
	while (*top != NULL)
	{
		tmp = * top;
		*top = (*top)->next;
		
//	printf("<%p> free delete\n", tmp->data);
		free(tmp->data);

//	printf("<%p> free delete\n", tmp);
		free(tmp);
	}

}



t_list	*reverse(t_list **top)
{
	t_list	*tmp;

	tmp = NULL;
	while (*top != NULL)
		push(&tmp, pop(top));
	return (tmp);
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

void	print_adr(t_list *lst)
{
	printf("start");
	while (lst)
	{
		printf("-->[%p]", (lst));
		lst = lst->next;
	}
	printf("-->[end]\n");
}

size_t	size_stack(t_list *top)
{
	size_t	size;

	size = 0;
	while (top != NULL)
	{
		size++;
		top = (top)->next;
	}
	return (size);
}

int	remove_position(t_list **top, size_t pos)
{
	t_list	*tmp;
	char	*n;

	tmp = NULL;
	if (pos >= size_stack(*top))
		return (-1);
	else
	{
		while (pos > 0)
		{
			n = pop(top);
			push(&tmp, n);
			pos--;
		}
		n = pop(top);
		while (tmp != NULL)
		{
			n = pop(&tmp);
			push(top, n);
		}
		return (0);
	}
}

char	*getitem(t_list *top, size_t pos)
{
	if (pos >= size_stack(top))
		return (NULL);
	else
	{
		while (pos > 0)
		{
			top = top->next;
			pos--;
		}
		return (top->data);
	}
}

void	trim_list(t_list **str)
{

	int	count_s;
	int	count_e;


	count_s = 0;
	count_e = 0;
	while (ft_strncmp(getitem(*str, 0)," ",1) == 0)
		pop(str);
	while (ft_strncmp(getitem(*str, size_stack(*str) - 1)," ", 1) == 0)
		remove_position(str, size_stack(*str) -1 );
}

char	*trim(char *line)
{
	int	i;
	int	j;
	int	count_s;
	int	count_e;
	char	*res;

	i = 0;
	j = 0;
	count_s = 0;
	count_e = 0;
	while (line[i] == ' ')
	{
		count_s++;
		if (line[i + 1] != ' ')
			break;
		i++;
	}
	i = ft_strlen(line);
	while (line[i] == ' ')
	{
		count_e++;
		if (line[i - 1] != ' ')
			break;
		i--;
	}
	res = malloc((ft_strlen(line) - count_s - count_e +1) * sizeof(char));
	if (res == NULL)
		exit(0);
	i = count_s;
	while (i < (int)ft_strlen(line) - count_e - count_s)
	{
		res[j] = line[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	getposition(t_list *top, char *item)
{
	int	i;
	int	len;

	len = ft_strlen(item);
	i = 0;
	while (top != NULL)
	{
		if (ft_strncmp(top->data, item, len) == 0)
			return (i);
		i++;
		top = top->next;
	}
	return (-1);
}

char	*getword(t_list **raw, char *search)
{
	int i;
	int	pos;
	char	*str;

	i = 0;
	pos = getposition(*raw, search);
	if (pos == -1)
		pos = size_stack(*raw);
	str = malloc((pos +1)* sizeof(char));
	while (i < pos)
	{
//		str[i] = *getitem(raw,i);
		str[i] = *pop(raw);
		i++;
	}
	str[i] = '\0';
	return (str);
}


void	create_raw_list(t_list **str, char *line)
{
	int	i;
	char	tmp[2];

	i = 0;
	while (line[i] != '\0')
	{
		tmp[0] = line[i];
		tmp[1] = '\0';
		push(str, tmp);
		i++;
	}
}


/* void	create_word(t_list **str, t_list **word)
{

}
 */
int main()
{


	t_list	*raw = NULL;
	t_list	*word = NULL;
//	t_list	*word = NULL;
	int i =0;
	char	*test1 = "echo | cat | awk '{print $3 \"\t\" $4}' > out.txt < marks.txt > out1.txt";
/* 	char	*test2 = "ls -l | cat";
	char	*test3 = "ls -l -a | cat > a.txt";
	char	*test4 = "echo | cat | awk '{print $3 \"\t\" $4}' > out.txt < marks.txt > out1.txt";
	 */
//	tmp1 = trim(test1);
//	printf("test trim [%s]\n", trim(test1));
	create_raw_list(&raw, test1);
	raw = reverse(&raw);
	printll(raw);
	trim_list(&raw);
	printll(raw);
	while (i < (int)size_stack(raw))
	{
		printf(" %d\t%s\n", i, getitem(raw,i));
		i++;
	}
	printll(raw);
	printf("space is at %d\n", getposition(raw, " "));
	push(&word,getword(&raw, " "));
	printll(word);
	printll(raw);
//  tout mettre dans word
	while (size_stack(raw ))
	{
		trim_list(&raw);
		push(&word,getword(&raw, " "));	
	}
	printll(raw);
	printf("\n\n");
	word = reverse(&word);
	printll(word);
	printf("\n\n size = %zu\n", size_stack(word));
	return (0);
}
