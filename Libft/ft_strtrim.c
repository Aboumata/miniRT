/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:34:40 by abdahman          #+#    #+#             */
/*   Updated: 2024/11/14 17:55:46 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*nstr;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j >= i && ft_strchr(set, s1[j]))
		j--;
	if (j < i)
	{
		nstr = malloc(1);
		if (!nstr)
			return (NULL);
		nstr[0] = '\0';
		return (nstr);
	}
	nstr = malloc(j - i + 2);
	if (!nstr)
		return (NULL);
	ft_strlcpy(nstr, s1 + i, j - i + 2);
	return (nstr);
}
