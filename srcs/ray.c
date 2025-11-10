/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 22:46:48 by aboumata          #+#    #+#             */
/*   Updated: 2025/11/06 22:46:49 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vector3	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.direction, t)));
}

t_ray	create_ray(t_data *data, int x, int y)
{
	t_vector3	viewport_point;
	t_vector3	horizontal_offset;
	t_vector3	vertical_offset;
	t_ray		ray;
	double		u;
	double		v;

	u = (double)x / (double)WIDTH;
	v = (double)y / (double)HEIGHT;
	horizontal_offset = vec_scale(data->cam.right, u
			* data->cam.viewport_width);
	vertical_offset = vec_scale(data->cam.up, -v * data->cam.viewport_height);
	viewport_point = vec_add(data->cam.top_left, horizontal_offset);
	viewport_point = vec_add(viewport_point, vertical_offset);
	ray.origin = data->scene->camera.pos;
	ray.direction = vec_sub(viewport_point, ray.origin);
	ray.direction = vec_normalize(ray.direction);
	return (ray);
}

// void	print_ray_info(t_ray ray, int x, int y) //just test the function if they are working
// {
//     printf("Pixel (%d, %d):\n", x, y);
//     printf("  Origin: (%.2f, %.2f, %.2f)\n",
//            ray.origin.x, ray.origin.y, ray.origin.z);
//     printf("  Direction: (%.2f, %.2f, %.2f)\n",
//            ray.direction.x, ray.direction.y, ray.direction.z);
//     printf("  Direction length: %.3f\n", vec_length(ray.direction));
//     printf("\n");
// }
//
// void	test_rays(t_data *data)
// {
//     t_ray	ray;
//
//     printf("=== Testing Ray Generation ===\n\n");
//
//     ray = create_ray(data, 0, 0);
//     print_ray_info(ray, 0, 0);
//
//     ray = create_ray(data, WIDTH - 1, 0);
//     print_ray_info(ray, WIDTH - 1, 0);
//
//     ray = create_ray(data, WIDTH / 2, HEIGHT / 2);
//     print_ray_info(ray, WIDTH / 2, HEIGHT / 2);
//
//     ray = create_ray(data, 0, HEIGHT - 1);
//     print_ray_info(ray, 0, HEIGHT - 1);
// }
