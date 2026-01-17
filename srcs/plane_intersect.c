/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:38:43 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/17 10:54:04 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_color	get_checkerboard_color(t_uv uv)
{
	int		u;
	int		v;

	u = floor(uv.u * 10.0);
	v = floor(uv.v * 10.0);
	if ((u + v) % 2 == 0)
		return ((t_color){255, 255, 255});
	return ((t_color){0, 0, 0});
}

static t_uv	get_plane_uv(t_vector3 p, t_planes *plane)
{
	t_uv		uv;
	t_vector3	u_axis;
	t_vector3	v_axis;
	t_vector3	n;

	n = plane->normal;
	if (fabs(n.y) > 0.9)
		u_axis = (t_vector3){1, 0, 0};
	else
		u_axis = vec_normalize(vec_cross((t_vector3){0, 1, 0}, n));
	v_axis = vec_normalize(vec_cross(n, u_axis));
	uv.u = vec_dot(vec_sub(p, plane->point), u_axis) * 0.1;
	uv.v = -vec_dot(vec_sub(p, plane->point), v_axis) * 0.1;
	return (uv);
}

static void	apply_plane_material(t_planes *plane, t_vector3 *normal,
		t_color *final_color, t_vector3 hit_point)
{
	t_uv	uv;

	if (plane->albedo_map || plane->bump_map || plane->checkerboard)
	{
		uv = get_plane_uv(hit_point, plane);
		if (plane->checkerboard)
			*final_color = get_checkerboard_color(uv);
		if (plane->albedo_map)
			*final_color = sample_texture_color(plane->albedo_map, uv);
		if (plane->bump_map)
			*normal = perturb_normal(*normal, plane->bump_map, uv);
	}
}

int	intersect_plane(t_ray ray, t_planes *plane, t_hit *hit)
{
	t_variables	var;
	t_vector3	normal;
	t_color		final_color;
	double		denom;

	denom = vec_dot(ray.direction, plane->normal);
	if (fabs(denom) < EPSILON)
		return (0);
	var.t = vec_dot(vec_sub(plane->point, ray.origin), plane->normal) / denom;
	if (!is_closer_hit(hit, var.t))
		return (0);
	var.hit_point = ray_at(ray, var.t);
	normal = plane->normal;
	final_color = plane->color;
	apply_plane_material(plane, &normal, &final_color, var.hit_point);
	if (vec_dot(normal, ray.direction) > 0)
		normal = vec_scale(normal, -1);
	var.hit = hit;
	update_hit(&var, normal, final_color);
	hit->object = plane;
	hit->type = PL;
	hit->shininess = plane->shininess;
	return (1);
}
