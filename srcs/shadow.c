/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:38:55 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/16 18:39:03 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	setup_shadow_ray(t_vector3 point, t_vector3 light_pos,
		t_ray *shadow_ray, double *light_distance)
{
	t_vector3	to_light;
	double		bias;

	to_light = vec_sub(light_pos, point);
	*light_distance = vec_length(to_light);
	if (*light_distance < EPSILON)
		return (0);
	shadow_ray->direction = vec_scale(to_light, 1.0 / *light_distance);
	bias = EPSILON * 10.0;
	shadow_ray->origin = vec_add(point,
			vec_scale(shadow_ray->direction, bias));
	return (1);
}

int	mandatory(t_object *obj, t_ray shadow_r, t_hit shadow_h, double l_d)
{
	if (obj->type == SP)
	{
		if (intersect_sphere(shadow_r, (t_spheres *)obj->obj, &shadow_h))
			if (shadow_h.t < l_d)
				return (1);
	}
	else if (obj->type == PL)
	{
		if (intersect_plane(shadow_r, (t_planes *)obj->obj, &shadow_h))
			if (shadow_h.t < l_d)
				return (1);
	}
	else if (obj->type == CY)
	{
		if (intersect_cylinder(shadow_r, (t_cylinders *)obj->obj,
				&shadow_h))
			if (shadow_h.t < l_d)
				return (1);
	}
	return (0);
}

int	bonus(t_object *obj, t_ray shadow_ray, t_hit shadow_hti, double l_d)
{
	if (obj->type == DISK)
	{
		if (intersect_disk(shadow_ray, (t_disk *)obj->obj, &shadow_hti))
			if (shadow_hti.t < l_d)
				return (1);
	}
	else if (obj->type == TRIANGLE)
	{
		if (intersect_triangle(shadow_ray, (t_triangle *)obj->obj,
				&shadow_hti))
			if (shadow_hti.t < l_d)
				return (1);
	}
	else if (obj->type == CONE)
	{
		if (intersect_cone(shadow_ray, (t_cone *)obj->obj, &shadow_hti))
			if (shadow_hti.t < l_d)
				return (1);
	}
	return (0);
}

static int	blocks_light(t_object *obj, t_ray shadow_ray,
		double light_distance)
{
	t_hit	shadow_hit;

	init_hit(&shadow_hit);
	if (mandatory(obj, shadow_ray, shadow_hit, light_distance))
		return (1);
	if (bonus(obj, shadow_ray, shadow_hit, light_distance))
		return (1);
	return (0);
}

int	is_in_shadow(t_vector3 point, t_vector3 normal, t_vector3 light_pos,
		t_scene *scene)
{
	t_ray		shadow_ray;
	t_object	*obj;
	double		light_distance;

	(void)normal;
	if (!setup_shadow_ray(point, light_pos, &shadow_ray, &light_distance))
		return (0);
	obj = scene->object;
	while (obj)
	{
		if (blocks_light(obj, shadow_ray, light_distance))
			return (1);
		obj = obj->next;
	}
	return (0);
}
