/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:30:37 by abdahman          #+#    #+#             */
/*   Updated: 2025/10/18 19:03:37 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	check_name(char *arg)
{
	size_t	len;

	len = strlen(arg) - 3;
	if (strcmp(".rt", arg + len) != 0)
		exit((perror("invalid file name.\n"), 1));
}

static void	check_file_content(t_scene *scene, char *arg)
{
	int		fd;
	char	*line;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
		exit((perror("file not exist.\n"), 1));
	line = get_next_line(fd);
	while (line)
	{
		parse_line(scene, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	parsing(t_scene *scene, char *arg)
{
	check_name(arg);
	check_file_content(scene, arg);
	if (!scene->has_ambient || !scene->has_camera)
		exit((perror("Missing required elements\n"), 1));
}
