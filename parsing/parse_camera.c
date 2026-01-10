/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 23:22:19 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/10 22:42:58 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_camera(t_scene *scene, char **token)
{
	if (count_tokens(token) != 4 || scene->has_camera > 0)
		exit((free_split(token), perror("Error: invalid camera\n"), 1));
	scene->has_camera++;
	scene->camera.pos = parse_vec(token, 1);
	scene->camera.dir = parse_vec(token, 2);
	if (!is_normalized(scene->camera.dir))
	{
		write(2, "Error: camera direction not normalized\n", 39);
		exit((free_split(token), 1));
	}
	scene->camera.fov = ft_atof(token[3], NULL);
	if (scene->camera.fov <= 0 || scene->camera.fov >= 180)
	{
		write(2, "Error: invalid FOV range\n", 25);
		exit((free_split(token), 1));
	}
}
