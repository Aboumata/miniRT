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

// void	print_camera_info(t_data *data)
		//just test the function if they are working
// {
// 	printf("\n=== Camera Setup Info ===\n\n");
// 	printf("Forward: (%f, %f, %f)\n", data->cam.forward.x, data->cam.forward.y,
// 		data->cam.forward.z);
// 	printf("Right: (%f, %f, %f)\n", data->cam.right.x, data->cam.right.y,
// 		data->cam.right.z);
// 	printf("Up: (%f, %f, %f)\n", data->cam.up.x, data->cam.up.y,
// 		data->cam.up.z);
// 	printf("\nViewport Width: %f\n", data->cam.viewport_width);
// 	printf("Viewport Height: %f\n", data->cam.viewport_height);
// 	printf("\nViewport Center: (%f, %f, %f)\n", data->cam.viewport_center.x,
// 		data->cam.viewport_center.y, data->cam.viewport_center.z);
// 	printf("Top-Left: (%f, %f, %f)\n", data->cam.top_left.x,
// 		data->cam.top_left.y, data->cam.top_left.z);
// 	printf("\n=== End Camera Info ===\n\n");
// }
