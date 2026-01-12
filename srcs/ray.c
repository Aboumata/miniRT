/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 22:46:48 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/09 18:35:17 by abdahman         ###   ########.fr       */
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

	double (u), v;
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
