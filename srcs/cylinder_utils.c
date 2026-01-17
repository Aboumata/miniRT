/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 10:30:13 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/17 10:34:59 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vector3	cylinder_body_normal(t_vector3 hit_point, t_cylinders *cylinder)
{
	t_vector3	v;
	t_vector3	projection;
	t_vector3	normal;
	double		proj_length;

	v = vec_sub(hit_point, cylinder->center);
	proj_length = vec_dot(v, cylinder->dir);
	projection = vec_scale(cylinder->dir, proj_length);
	normal = vec_sub(v, projection);
	normal = vec_normalize(normal);
	return (normal);
}

t_color	get_cylinder_checkerboard(t_uv uv)
{
	int	u;
	int	v;

	u = floor(uv.u * 10);
	v = floor(uv.v * 10);
	if ((u + v) % 2 == 0)
		return ((t_color){255, 255, 255});
	return ((t_color){0, 0, 0});
}

static t_uv	get_cap_uv(t_vector3 p, t_vector3 center, t_vector3 normal)
{
	t_uv		uv;
	t_vector3	u_axis;
	t_vector3	v_axis;

	if (fabs(normal.y) > 0.9)
		u_axis = (t_vector3){1, 0, 0};
	else
		u_axis = vec_normalize(vec_cross((t_vector3){0, 1, 0}, normal));
	v_axis = vec_normalize(vec_cross(normal, u_axis));
	uv.u = vec_dot(vec_sub(p, center), u_axis);
	uv.v = vec_dot(vec_sub(p, center), v_axis);
	return (uv);
}

static t_color	get_cap_col(t_cylinders *cy, t_vector3 p,
		t_vector3 c, t_vector3 n)
{
	if (cy->checkerboard)
		return (get_cylinder_checkerboard(get_cap_uv(p, c, n)));
	return (cy->color);
}

int	check_one_cap(t_ray ray, t_cylinders *cy, t_hit *hit, double sign)
{
	t_variables	var;
	t_vector3	cap_c;
	t_vector3	norm;
	double		denom;

	denom = vec_dot(ray.direction, cy->dir);
	if (fabs(denom) < EPSILON)
		return (0);
	cap_c = vec_add(cy->center, vec_scale(cy->dir, cy->height / 2.0 * sign));
	var.t = vec_dot(vec_sub(cap_c, ray.origin), cy->dir) / denom;
	if (!is_closer_hit(hit, var.t))
		return (0);
	var.hit_point = ray_at(ray, var.t);
	if (vec_dot(vec_sub(var.hit_point, cap_c),
			vec_sub(var.hit_point, cap_c)) > pow(cy->diameter / 2.0, 2))
		return (0);
	norm = vec_scale(cy->dir, sign);
	var.hit = hit;
	update_hit(&var, norm, get_cap_col(cy, var.hit_point, cap_c, norm));
	hit->object = cy;
	hit->type = CY;
	hit->shininess = cy->shininess;
	return (1);
}
