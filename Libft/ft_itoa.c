/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:55:15 by abdahman          #+#    #+#             */
/*   Updated: 2024/11/17 18:17:48 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	l;
	int		len;
	char	*str;

	l = n;
	len = count(l);
	str = malloc (len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (l < 0)
	{
		str[0] = '-';
		l = -l;
	}
	if (l == 0)
		str[0] = '0';
	len--;
	while (l > 0)
	{
		str[len] = (l % 10) + 48;
		l /= 10;
		len--;
	}
	return (str);
}
