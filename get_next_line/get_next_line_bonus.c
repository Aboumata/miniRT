/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:03:28 by abdahman          #+#    #+#             */
/*   Updated: 2024/12/23 23:16:24 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

static char	*ft_read_line(int fd, char *stored)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	if (!stored)
		stored = ft_strdup("");
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stored, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free(buffer, stored));
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(stored, buffer);
		if (!temp)
			return (ft_free(buffer, stored));
		free(stored);
		stored = temp;
	}
	free(buffer);
	return (stored);
}

static char	*ft_get_line(char *stored)
{
	int		i;
	char	*line;

	i = 0;
	if (!stored || !stored[0])
		return (NULL);
	while (stored[i] && stored[i] != '\n')
		i++;
	if (stored[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
	{
		line[i] = stored[i];
		i++;
	}
	if (stored[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_store_remaining(char *stored)
{
	int		i;
	int		j;
	char	*remaining;

	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
	{
		free(stored);
		return (NULL);
	}
	remaining = malloc(sizeof(char) * (ft_strlen(stored) - i + 1));
	if (!remaining)
	{
		free(stored);
		return (NULL);
	}
	i++;
	j = 0;
	while (stored[i])
		remaining[j++] = stored[i++];
	remaining[j] = '\0';
	free(stored);
	return (remaining);
}

char	*get_next_line(int fd)
{
	static char	*stored[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	stored[fd] = ft_read_line(fd, stored[fd]);
	if (!stored[fd])
		return (NULL);
	line = ft_get_line(stored[fd]);
	if (!line)
	{
		free(stored[fd]);
		stored[fd] = NULL;
		return (NULL);
	}
	stored[fd] = ft_store_remaining(stored[fd]);
	return (line);
}
