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
	printf("<%p> push\n", tmp);
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
	printf("<%p> free pop -data\n", tmp->data);
	free(tmp->data);

	printf("<%p> free pop -struct\n", tmp);
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
		
	printf("<%p> free delete\n", tmp->data);
		free(tmp->data);

	printf("<%p> free delete\n", tmp);
		free(tmp);
	}

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
	printf("Taille stack =%zu\n", size);
	return (size);
}

/*
int	permut(t_list **top)
{// pas de *top sinon erreur et faut rajouter test faisabilité
	int	t1;
	int	t2;

	if (size_stack(*top) >= 2)
	{
		t1 = pop(top);
		t2 = pop(top);
		push(top, t1);
		push(top, t2);
		return (1);
	}
	return (0);
}

int	permut_2(t_list **a, t_list **b)
{// fait ss

	if (size_stack(*a) >= 2 && size_stack(*b) >= 2)
	{
		permut(a);
		permut(b);
		return (1);
	}
	return (0);
}

int	transfer(t_list **start, t_list **end)
{
	int	n;

	if (size_stack(*start) >= 1)
	{
		n = pop(start);
		push(end, n);
		return (1);
	}
	return (0);
}

int	put_end(t_list **top)
{ // à tester
	int	n;
	t_list	*tmp;

	tmp = NULL;
	if (size_stack(*top) >= 1)
	{
//		printf("top %p\n",*top);
		n = pop(top);
//		printf("put end n %d\n",n);
		while (*top != NULL)
		{
			printf("top %p\n",*top);
			transfer(top, &tmp);
		}
//		printll(tmp);
		push(top,n);
		while (tmp != NULL)
		{
			n = pop(&tmp);
			push(top, n);
		}
//		printll(*top);
		printf("tmp = %p\n",tmp);
		return (1);
	}
	return (0);
}

int	put_start(t_list **top)
{// à tester
	int	n;
	int	m;
	t_list	*tmp;

	tmp = NULL;
	if (size_stack(*top) >= 1)
	{
		while (*top != NULL)
			transfer(top, &tmp);
		printll(tmp);
		m = pop(&tmp);
		printll(tmp);
		while (tmp != NULL)
		{
			n = pop(&tmp);
			push(top, n);
		}
		push(top, m);
		printll(*top);
		return (1);
	}
	return (0);
}

*/

void	test_input(t_list **s, char *tmp)
{// il faut comparer le nb de fois cette func activée avec le nb de gnl
	if (ft_strncmp(tmp, "sa\n", 3) == 0)
		push(s, tmp);
	if (ft_strncmp(tmp, "sb\n", 3) == 0)
		push(s, tmp);
	if (ft_strncmp(tmp, "ss\n", 3) == 0)
		push(s, tmp);
	if (ft_strncmp(tmp, "ra\n", 3) == 0)
		push(s, tmp);
	if (ft_strncmp(tmp, "rb\n", 3) == 0)
		push(s, tmp);
	if (ft_strncmp(tmp, "rr\n", 3) == 0)
		push(s, tmp);
	if (ft_strncmp(tmp, "rra\n", 4) == 0)
		push(s, tmp);
	if (ft_strncmp(tmp, "rrb\n", 4) == 0)
		push(s, tmp);
	if (ft_strncmp(tmp, "rrr\n", 4) == 0)
		push(s, tmp);
	if (ft_strncmp(tmp, "pa\n", 3) == 0)
		push(s, tmp);
	if (ft_strncmp(tmp, "pb\n", 3) == 0)
		push(s, tmp);
}

int main()
{
	char	*tmp ;
	t_list	*s = NULL;


	push(&s, "elem 1");
	push(&s, "elem 2");
	push(&s, "a");
	printll(s);
	tmp = pop(&s);
	printll(s);
	printf(" string popped = [%s]\n", tmp);
	printf("<%p> free main\n", tmp);
	free(tmp);
	delete(&s);
	return (0);
}
