/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:36:02 by abdahman          #+#    #+#             */
/*   Updated: 2024/12/23 23:04:16 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*nstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	nstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!nstr)
		return (NULL);
	while (s1[i])
	{
		nstr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		nstr[i + j] = s2[j];
		j++;
	}
	nstr[i + j] = '\0';
	return (nstr);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i++;
	}
	if (str && str[i] == '\0' && c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strdup(char *str)
{
	char	*nstr;
	int		i;

	i = 0;
	nstr = malloc(ft_strlen(str) + 1);
	if (!nstr)
		return (NULL);
	while (str[i])
	{
		nstr[i] = str[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
