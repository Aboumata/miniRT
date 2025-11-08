/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 23:56:48 by aboumata          #+#    #+#             */
/*   Updated: 2025/11/07 23:56:50 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	setup_camera(t_data *data)
{
	t_vector3	world_up;
	t_vector3	cam_pos;
	t_vector3	left_offset;
	t_vector3	up_offset;
	double		distance;
	double		fov_rad;
	double		aspect;

	distance = 1.0;
	world_up.x = 0;
	world_up.y = 1;
	world_up.z = 0;
	aspect = (double)WIDTH / (double)HEIGHT;
	fov_rad = data->scene->camera.fov * (PI / 180.0);
	cam_pos = data->scene->camera.pos;
	data->cam.forward = data->scene->camera.dir;
	data->cam.right = vec_normalize(vec_cross(world_up, data->cam.forward));
	data->cam.up = vec_normalize(vec_cross(data->cam.forward, data->cam.right));
	data->cam.viewport_height = 2.0 * distance * tan(fov_rad / 2.0);
	data->cam.viewport_width = data->cam.viewport_height * aspect;
	data->cam.viewport_center = vec_add(cam_pos, vec_scale(data->cam.forward,
				1.0));
	left_offset = vec_scale(data->cam.right, data->cam.viewport_width / 2.0);
	up_offset = vec_scale(data->cam.up, data->cam.viewport_height / 2.0);
	data->cam.top_left = vec_sub(vec_add(data->cam.viewport_center, up_offset),
			left_offset);
}
