/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:32:37 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 11:02:34 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		result[i++] = *s1++;
	while (s2 && *s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	while (s && *s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*ptr;
	size_t	len_src;

	if (!src)
		return (NULL);
	len_src = ft_strlen(src);
	ptr = (char *)malloc(len_src + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr2(const char *src, size_t start, size_t len)
{
	size_t	len_src;
	size_t	i;
	char	*result;

	if (src == NULL)
		return (NULL);
	len_src = ft_strlen(src);
	if (start >= len_src)
		return (ft_strdup(""));
	if (start + len > len_src)
		len = len_src - start;
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len && src[start + i] != '\0')
	{
		result[i] = src[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
