/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 22:36:09 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 15:32:31 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	mandatory(t_object *obj, t_ray shadow_r, t_hit shadow_h, double l_d)
{
	if (obj->type == SP)
	{
		if (intersect_sphere(shadow_r, (t_spheres *)obj->obj,
				&shadow_h))
			if (shadow_h.t < l_d)
				return (1);
	}
	else if (obj->type == PL)
	{
		if (intersect_plane(shadow_r, (t_planes *)obj->obj, &shadow_h))
		{
			if (shadow_h.t < l_d)
				return (1);
		}
	}
	else if (obj->type == CY)
	{
		if (intersect_cylinder(shadow_r, (t_cylinders *)obj->obj, &shadow_h))
		{
			if (shadow_h.t < l_d)
				return (1);
		}
	}
	return (0);
}

int	bonus(t_object *obj, t_ray shadow_ray, t_hit shadow_hti, double l_d)
{
	if (obj->type == DISK)
	{
		if (intersect_disk(shadow_ray, (t_disk *)obj->obj, &shadow_hti))
		{
			if (shadow_hti.t < l_d)
				return (1);
		}
	}
	else if (obj->type == TRIANGLE)
	{
		if (intersect_triangle(shadow_ray, (t_triangle *)obj->obj, &shadow_hti))
		{
			if (shadow_hti.t < l_d)
				return (1);
		}
	}
	else if (obj->type == CONE)
	{
		if (intersect_cone(shadow_ray, (t_cone *)obj->obj, &shadow_hti))
		{
			if (shadow_hti.t < l_d)
				return (1);
		}
	}
	return (0);
}

int	is_in_shadow(t_vector3 point, t_vector3 normal, t_vector3 light_pos,
		t_scene *scene)
{
	t_ray		shadow_ray;
	t_vector3	to_light;
	t_hit		shadow_hti;
	t_object	*obj;

	double (light_distance), i = 0.0;
	to_light = vec_sub(light_pos, point);
	light_distance = vec_length(to_light);
	shadow_ray.origin = vec_add(point, vec_scale(normal, EPSILON));
	shadow_ray.direction = vec_normalize(to_light);
	obj = scene->object;
	while (obj)
	{
		init_hit(&shadow_hti);
		i += mandatory(obj, shadow_ray, shadow_hti, light_distance);
		i += bonus(obj, shadow_ray, shadow_hti, light_distance);
		if (i)
			return (i);
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
