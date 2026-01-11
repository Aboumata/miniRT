/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 23:22:19 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 10:53:24 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_camera(t_scene *scene, char **token)
{
	if (count_tokens(token) != 4 || scene->has_camera > 0)
		ft_perror(token, scene, "Error: invalid camera\n");
	scene->has_camera++;
	scene->camera.pos = parse_vec(token, 1, scene);
	scene->camera.dir = parse_vec(token, 2, scene);
	if (!is_normalized(scene->camera.dir))
	{
		write(2, "Error: camera direction not normalized\n", 39);
		ft_perror(token, scene, NULL);
	}
	scene->camera.fov = ft_atof(token[3], NULL);
	if (scene->camera.fov <= 0 || scene->camera.fov >= 180)
	{
		write(2, "Error: invalid FOV range\n", 25);
		ft_perror(token, scene, NULL);
	}
}
