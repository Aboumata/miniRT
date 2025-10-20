/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 23:22:19 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/16 23:22:21 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_camera(t_scene *scene, char **token)
{
	if (count_tokens(token) != 4 || scene->has_camera > 0)
		exit((perror("Error: invalid camera\n"), 1));
	scene->has_camera++;
	scene->camera.pos = parse_vec(token[1]);
	scene->camera.dir = parse_vec(token[2]);
	if (!is_normalized(scene->camera.dir))
		exit((perror("Error: camera direction not normalized\n"), 1));
	scene->camera.fov = ft_atof(token[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		exit((perror("Error: invalid FOV range\n"), 1));
}
