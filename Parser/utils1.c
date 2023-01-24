/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:54:03 by jsollett          #+#    #+#             */
/*   Updated: 2023/01/24 15:02:14 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	if (c == '?')
		return (63);
	return (0);
}

int	ft_isnum(char c, int pos)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9' && pos == 0)
		return (-1);
	if (c >= '0' && c <= '9' && pos != 0)
		return (1);
	if (c == '?')
		return (63);
	return (0);
}

static	size_t	ft_intlen(int n)
{
	int		result;
	size_t	count;

	result = n;
	count = 0;
	if (n <= 0)
		count++;
	while (result != 0)
	{
		result = result / 10;
		count++;
	}
	return (count);
}

static	int	power_10(int expo)
{
	int	result;

	result = 1;
	while (expo != 0)
	{
		result *= 10;
		expo--;
	}
	return (result);
}

char	*ft_itoa(int nb)
{
	char	*ia;
	int		i;
	int		j;

	i = ft_intlen(nb);
	ia = (char *)malloc((i + 1) * sizeof(char));
	if (ia == NULL)
		return (NULL);
	if (nb < 0)
	{
		(*ia++) = (char)('-');
		i--;
	}
	while (i)
	{
		j = (nb / power_10(i - 1)) % 10;
		if (j < 0)
			j = -j;
		*(ia++) = (char)(j + '0');
		i--;
	}
	*ia = '\0';
	return (ia - ft_intlen(nb));
}
