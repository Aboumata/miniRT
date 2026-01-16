/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:30:37 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/16 10:50:17 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	check_name(char *arg)
{
	size_t	len;

	len = strlen(arg) - 3;
	if (strcmp(".rt", arg + len) != 0)
		exit((perror("Error: invalid file name.\n"), 1));
}

static void	check_file_content(t_scene *scene, char *arg)
{
	int		fd;
	char	*line;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
		ft_perror(NULL, scene, "Error: file not exist.\n");
	scene->mlx = mlx_init();
	if (!scene->mlx)
		ft_perror(NULL, scene, "Error: MLX initialization failed\n");
	line = get_next_line(fd);
	while (line)
	{
		parse_line(scene, line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	parsing(t_scene *scene, char *arg)
{
	check_name(arg);
	check_file_content(scene, arg);
	if (!scene->has_ambient || !scene->has_camera)
	{
		ft_free_all(&scene->mem);
		ft_perror(NULL, scene, "Error: Missing required elements\n");
	}
}
