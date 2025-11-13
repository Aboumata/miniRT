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
	t_ray shadow_ray;
	t_vector3 to_light;
	double light_distance;
	t_hit shadow_hti;
	t_object *obj;

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
			t_spheres *sphere;
			sphere = (t_spheres *)obj->obj;
			if (intersect_sphere(shadow_ray, sphere, &shadow_hti))
				if (shadow_hti.t < light_distance)
					return (1);
		}
		obj = obj->next;
	}
	return (0);
}