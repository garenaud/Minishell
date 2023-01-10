/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:02:50 by grenaud-          #+#    #+#             */
/*   Updated: 2022/12/28 15:52:36 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (str != NULL)
	{
		while (*str != '\0')
		{
			str++;
			count++;
		}
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

char	*ft_strcpy(char *dest, const char *src)
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

char	*ft_strdup(char *src)
{
	char	*dst;

	dst = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	ft_strcpy(dst, src);
	return (dst);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (((n -1) > 0) && (*s1 != '\0') && (*s2 != '\0') && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*s1 -(unsigned char)*s2);
}
