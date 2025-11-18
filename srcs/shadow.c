/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 22:36:09 by aboumata          #+#    #+#             */
/*   Updated: 2025/11/12 22:36:11 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	is_in_shadow(t_vector3 point, t_vector3 normal, t_vector3 light_pos,
		t_scene *scene)
{
	t_ray		shadow_ray;
	t_vector3	to_light;
	double		light_distance;
	t_hit		shadow_hti;
	t_object	*obj;

	to_light = vec_sub(light_pos, point);
	light_distance = vec_length(to_light);
	shadow_ray.origin = vec_add(point, vec_scale(normal, EPSILON));
	shadow_ray.direction = vec_normalize(to_light);
	obj = scene->object;
	while (obj)
	{
		init_hit(&shadow_hti);
		if (obj->type == SP)
		{
			if (intersect_sphere(shadow_ray, (t_spheres *)obj->obj,
					&shadow_hti))
				if (shadow_hti.t < light_distance)
					return (1);
		}
		else if (obj->type == PL)
		{
			if (intersect_plane(shadow_ray, (t_planes *)obj->obj, &shadow_hti))
			{
				if (shadow_hti.t < light_distance)
					return (1);
			}
		}
		else if (obj->type == CY)
		{
			if (intersect_cylinder(shadow_ray, (t_cylinders *)obj->obj, &shadow_hti))
			{
				if (shadow_hti.t < light_distance)
					return (1);
			}
		}
		obj = obj->next;
	}
	return (0);
}

// void	test_shadow(t_data *data)
// {
// 	t_vector3	test_point;
// 	t_vector3	test_normal;
// 	t_light		*light;
// 	int			in_shadow;
//
// 	printf("\n=== Testing Shadow Rays ===\n\n");
//
// 	test_point.x = 0;
// 	test_point.y = 0;
// 	test_point.z = 5;
//
// 	test_normal.x = 0;
// 	test_normal.y = 1;
// 	test_normal.z = 0;
//
// 	printf("Test point: (%.2f, %.2f, %.2f)\n",
// 		test_point.x, test_point.y, test_point.z);
// 	printf("Normal: (%.2f, %.2f, %.2f)\n\n",
// 		test_normal.x, test_normal.y, test_normal.z);
//
// 	light = data->scene->light;
// 	while (light)
// 	{
// 		printf("Testing light at (%.2f, %.2f, %.2f):\n",
// 			light->pos.x, light->pos.y, light->pos.z);
//
// 		in_shadow = is_in_shadow(test_point, test_normal,
// 			light->pos, data->scene);
//
// 		if (in_shadow)
// 			printf("  ✗ IN SHADOW\n\n");
// 		else
// 			printf("  ✓ LIT\n\n");
//
// 		light = light->next;
// 	}
// }
