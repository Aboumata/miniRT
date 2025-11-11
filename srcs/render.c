/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:58:21 by aboumata          #+#    #+#             */
/*   Updated: 2025/11/05 02:58:22 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	get_pixel_color(t_hit *hit, t_scene *scene)
{
	t_color lit_color;
	if (hit->hit)
	{
		lit_color = calculate_lighting(hit, scene);
		return (create_color(lit_color.r, lit_color.g, lit_color.b));
	}

	return (create_color(0, 0, 0));
}

static void	trace_spheres(t_ray ray, t_scene *scene, t_hit *hit)
{
	t_object	*obj;
	t_spheres	*sphere;

	obj = scene->object;
	while (obj)
	{
		if (obj->type == SP)
		{
			sphere = (t_spheres *)obj->obj;
			intersect_sphere(ray, sphere, hit);
		}
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
			trace_spheres(ray, data->scene, &hit);
			color = get_pixel_color(&hit, data->scene);
			put_pixel(data, x, y, color);
			x++;
		}
		y++;
	}
	printf("Done! Putting image to window...\n");
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
