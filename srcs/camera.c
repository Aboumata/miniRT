/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 23:56:48 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/09 18:17:56 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	setup_camera(t_data *data)
{
	t_vector3	world_up;
	t_vector3	cam_pos;
	t_vector3	left_offset;
	t_vector3	up_offset;

	double (distance), fov_rad, aspect;
	distance = 1.0;
	world_up.x = 0;
	world_up.y = 1;
	world_up.z = 0;
	aspect = (double)WIDTH / (double)HEIGHT;
	fov_rad = data->scene->camera.fov * (PI / 180.0);
	cam_pos = data->scene->camera.pos;
	data->cam.forward = data->scene->camera.dir;
	data->cam.right = vec_normalize(vec_cross(data->cam.forward, world_up));
	data->cam.up = vec_normalize(vec_cross(data->cam.right, data->cam.forward));
	data->cam.viewport_height = 2.0 * distance * tan(fov_rad / 2.0);
	data->cam.viewport_width = data->cam.viewport_height * aspect;
	data->cam.viewport_center = vec_add(cam_pos, vec_scale(data->cam.forward,
				1.0));
	left_offset = vec_scale(data->cam.right, data->cam.viewport_width / 2.0);
	up_offset = vec_scale(data->cam.up, data->cam.viewport_height / 2.0);
	data->cam.top_left = vec_sub(vec_add(data->cam.viewport_center, up_offset),
			left_offset);
}
