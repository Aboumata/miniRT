/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:38:43 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/16 18:38:44 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_color	update_color(int r, int g, int b, t_color color)
{
	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color	get_checkerboard_color(t_vector3 hit_p)
{
	float	size;
	int		x;
	int		y;
	int		z;

	size = 1 / 10.0;
	x = floor(hit_p.x) * size;
	z = floor(hit_p.z) * size;
	y = floor(hit_p.y) * size;
	if ((x + y + z) % 2 == 0)
		return ((t_color){255, 255, 255});
	else
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

int	intersect_plane(t_ray ray, t_planes *plane, t_hit *hit)
{
	t_vector3	to_plane;
	t_variables	var;
	t_vector3	normal;
	t_uv		uv;
	t_color		final_color;
	double		denom;
	double		numer;

	normal = plane->normal;
	var.hit = hit;
	denom = vec_dot(ray.direction, normal);
	if (fabs(denom) < EPSILON)
		return (0);
	if (denom > 0)
		normal = vec_scale(normal, -1);
	to_plane = vec_sub(plane->point, ray.origin);
	numer = vec_dot(to_plane, plane->normal);
	var.t = numer / denom;
	if (var.t < EPSILON || var.t > var.hit->t)
		return (0);
	var.hit_point = ray_at(ray, var.t);
	final_color = plane->color;
	if (plane->checkerboard)
		final_color = get_checkerboard_color(var.hit_point);
	if (plane->albedo_map || plane->bump_map)
	{
		uv = get_plane_uv(var.hit_point, plane);
		if (plane->albedo_map)
			final_color = sample_texture_color(plane->albedo_map, uv);
		if (plane->bump_map)
			normal = perturb_normal(normal, plane->bump_map, uv);
	}
	if (vec_dot(normal, ray.direction) > 0)
		normal = vec_scale(normal, -1);
	update_hit(&var, normal, final_color);
	hit->normal = normal;
	hit->object = plane;
	hit->type = PL;
	hit->shininess = plane->shininess;
	return (1);
}
