/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:04:54 by jsollett          #+#    #+#             */
/*   Updated: 2022/06/30 11:04:57 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*ft_strjoin(char const *src1, char const *src2)
{
	char	*dst;
	size_t	len1;
	size_t	len2;

	if (src1 == NULL || src2 == NULL)
		return (NULL);
	len1 = ft_strlen_c(src1, '\0');
	len2 = ft_strlen_c(src2, '\0');
	dst = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	*(dst + len1 + len2) = '\0';
	while (len2)
	{
		len2--;
		*(dst + len1 + len2) = *(src2 + len2);
	}
	while (len1)
	{
		len1--;
		*(dst + len1) = *(src1 + len1);
	}
	return (dst);
}

size_t	ft_count(const char *ss, char del, size_t count, size_t i)
{
	size_t	len;

	len = ft_strlen_c(ss, '\0');
	while (*(ss + i) != '\0')
	{
		while (*(ss + i) == del && i < len)
		{
			i++;
			if (i == len)
				return (count++);
		}
		count++;
		while (*(ss + i) != del && i < len)
		{
			i++;
			if (i == len)
				return (count++);
		}
	}
	return (count);
}

char	*ft_word(char *word, const char *src, size_t i, size_t offset)
{
	size_t	j;

	j = 0;
	while (j < offset)
	{
		*(word + j) = *(src + i + j);
		j++;
	}
	*(word + offset) = '\0';
	return (word);
}

char	**ft_word1(char **array, const char *src, char c, size_t nw)
{
	char	*word;
	size_t	offset;
	size_t	index;

	index = 0;
	while (*(src + index) != '\0')
	{
		if (*(src + index) == c)
			index++;
		offset = ft_strlen_c(src + index, c);
		if (offset != 0)
		{
			word = malloc((offset + 1) * sizeof(char));
			if (word == NULL)
				return (NULL);
			array[nw] = ft_word(word, src, index, offset);
			index = index + offset;
			nw++;
		}
	}
	return (array);
}
