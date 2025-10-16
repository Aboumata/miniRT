/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 20:00:34 by abdahman          #+#    #+#             */
/*   Updated: 2024/11/18 18:55:59 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char b)
{
	int	i;
	int	n;
	int	checker;

	i = 0;
	n = 0;
	checker = 1;
	while (str[i])
	{
		if (str[i] != b && checker == 1)
			n++;
		checker = 0;
		if (str[i] == b)
			checker = 1;
		i++;
	}
	return (n);
}

char	**free_ss(char **nstr, int i)
{
	while (i-- > 0)
		free(nstr[i]);
	free(nstr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	size_t	start;
	size_t	len;
	char	**nstr;

	if (!s)
		return (NULL);
	nstr = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!nstr)
		return (NULL);
	i = -1;
	start = 0;
	while (++i < count_words(s, c))
	{
		while (s[start] == c)
			start++;
		len = 0;
		while (s[start + len] && s[start + len] != c)
			len++;
		nstr[i] = ft_substr(s, start, len);
		if (!nstr[i])
			return (free_ss(nstr, i));
		start += len;
	}
	return (nstr[i] = NULL, nstr);
}
