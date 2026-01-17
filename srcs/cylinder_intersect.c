/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:33:14 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/17 10:34:25 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	intersect_cylinder_caps(t_ray ray, t_cylinders *cy, t_hit *hit)
{
	int	hit_top;
	int	hit_bot;

	hit_top = check_one_cap(ray, cy, hit, 1.0);
	hit_bot = check_one_cap(ray, cy, hit, -1.0);
	return (hit_top || hit_bot);
}

static int	solve_cylinder_quadratic(t_ray ray, t_cylinders *cy, double *t)
{
	t_vector3	oc;
	t_vector3	perp[2];
	double		coeff[3];
	double		disc;

	oc = vec_sub(ray.origin, cy->center);
	perp[0] = vec_sub(oc, vec_scale(cy->dir, vec_dot(oc, cy->dir)));
	perp[1] = vec_sub(ray.direction,
			vec_scale(cy->dir, vec_dot(ray.direction, cy->dir)));
	coeff[0] = vec_dot(perp[1], perp[1]);
	coeff[1] = 2.0 * vec_dot(perp[0], perp[1]);
	coeff[2] = vec_dot(perp[0], perp[0]) - pow(cy->diameter / 2.0, 2);
	disc = coeff[1] * coeff[1] - 4 * coeff[0] * coeff[2];
	if (disc < 0)
		return (0);
	*t = (-coeff[1] - sqrt(disc)) / (2.0 * coeff[0]);
	return (1);
}

static void	apply_cylinder_texture(t_cylinders *cy, t_variables *var,
		t_vector3 *normal, t_color *color)
{
	t_uv	uv;

	if (cy->bump_map || cy->albedo_map || cy->checkerboard)
	{
		uv = cylinder_uv(var->hit_point, cy);
		if (cy->bump_map)
			*normal = perturb_normal(*normal, cy->bump_map, uv);
		if (cy->checkerboard)
			*color = get_cylinder_checkerboard(uv);
		if (cy->albedo_map)
			*color = sample_texture_color(cy->albedo_map, uv);
		else if (cy->bump_map)
			*color = sample_texture_color(cy->bump_map, uv);
	}
}

static int	intersect_cylinder_body(t_ray ray, t_cylinders *cy, t_hit *hit)
{
	t_variables	var;
	t_vector3	normal;
	t_color		col;
	double		h;

	if (!solve_cylinder_quadratic(ray, cy, &var.t))
		return (0);
	if (!is_closer_hit(hit, var.t))
		return (0);
	var.hit_point = ray_at(ray, var.t);
	h = vec_dot(vec_sub(var.hit_point, cy->center), cy->dir);
	if (fabs(h) > cy->height / 2.0)
		return (0);
	normal = cylinder_body_normal(var.hit_point, cy);
	col = cy->color;
	apply_cylinder_texture(cy, &var, &normal, &col);
	if (vec_dot(normal, ray.direction) > 0)
		normal = vec_scale(normal, -1);
	var.hit = hit;
	update_hit(&var, normal, col);
	hit->object = cy;
	hit->type = CY;
	hit->shininess = cy->shininess;
	return (1);
}

int	intersect_cylinder(t_ray ray, t_cylinders *cylinder, t_hit *hit)
{
	int	body_hit;
	int	cap_hit;

	body_hit = intersect_cylinder_body(ray, cylinder, hit);
	cap_hit = intersect_cylinder_caps(ray, cylinder, hit);
	return (body_hit || cap_hit);
}
