/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:43:28 by grenaud-          #+#    #+#             */
/*   Updated: 2022/11/07 11:30:29 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	t_list	*raw = NULL;
	t_list	*word = NULL;
	t_list_i	*dquote = NULL;
	t_list_i	*squote = NULL;
//	t_list	*word = NULL;
	int i =0;
	char	*tmp;
	char	*test1 = " \" abc \' 123 \' abc \"\"sdakjfhjsdkahf\"";
//	char	*test0 = "echo | cat | awk '{print $3 \" \t \" $4}' > out.txt < marks.txt > out1.txt";
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
	create_quote_list(&raw, &dquote, "\"");
	create_quote_list(&raw, &squote, "\'");

	printll_int(dquote);
	printll_int(squote);
	inclusion(&squote, &dquote, 1, 1);
//	push(&word,getword1(&raw, " "));
//	printll(word);
	printll(raw);
//  tout mettre dans word
	while (size_stack(raw ))
	{
		trim_list(&raw);
		tmp = getword1(&raw, " ");
		if (ft_strncmp(tmp,"", 1))
		{
			printf("tmp = [%s]\n", tmp);
			push(&word,tmp);	
		}
		else
			printf("tmp vide= [%s]\n", tmp);
	}
	printll(raw);
	printf("\n\n");
	word = reverse(&word);
	printll(word);
	printf("\n\n size = %zu\n", size_stack(word));
	printf("\n\n nouveau minishell\n");
	return (0);
}
