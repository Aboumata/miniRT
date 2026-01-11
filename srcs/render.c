/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:58:21 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 15:31:44 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	get_pixel_color(t_hit *hit, t_scene *scene)
{
	t_color	lit_color;

	if (hit->hit)
	{
		lit_color = calculate_lighting(hit, scene);
		return (create_color(lit_color.r, lit_color.g, lit_color.b));
	}
	return (create_color(0, 0, 0));
}

static void	trace_objects(t_ray ray, t_scene *scene, t_hit *hit)
{
	t_object	*obj;

	obj = scene->object;
	while (obj)
	{
		if (obj->type == SP)
			intersect_sphere(ray, (t_spheres *)obj->obj, hit);
		else if (obj->type == PL)
			intersect_plane(ray, (t_planes *)obj->obj, hit);
		else if (obj->type == CY)
			intersect_cylinder(ray, (t_cylinders *)obj->obj, hit);
		else if (obj->type == DISK)
			intersect_disk(ray, (t_disk *)obj->obj, hit);
		else if (obj->type == TRIANGLE)
			intersect_triangle(ray, (t_triangle *)obj->obj, hit);
		else if (obj->type == CONE)
			intersect_cone(ray, (t_cone *)obj->obj, hit);
		obj = obj->next;
	}
}

void	render(t_data *data)
{
	int		x;
	int		y;
	t_ray	ray;
	t_hit	hit;
	int		color;

	printf("Rendering...\n");
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = create_ray(data, x, y);
			init_hit(&hit);
			trace_objects(ray, data->scene, &hit);
			color = get_pixel_color(&hit, data->scene);
			put_pixel(data, x, y, color);
			x++;
		}
		y++;
	}
	printf("Done! Putting image to window...\n");
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
