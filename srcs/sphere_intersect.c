/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:32:47 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/17 11:40:50 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static t_vector3	sphere_normal(t_vector3 hit_point, t_vector3 center)
{
	t_vector3	normal;

	normal = vec_sub(hit_point, center);
	normal = vec_normalize(normal);
	return (normal);
}

static int	solve_sphere_quadratic(t_ray ray, t_spheres *sp, double *t)
{
	t_vector3	oc;
	double		a;
	double		half_b;
	double		c;
	double		disc;

	oc = vec_sub(ray.origin, sp->center);
	a = vec_dot(ray.direction, ray.direction);
	half_b = vec_dot(oc, ray.direction);
	c = vec_dot(oc, oc) - (sp->diameter / 2.0) * (sp->diameter / 2.0);
	disc = half_b * half_b - a * c;
	if (disc < 0)
		return (0);
	*t = (-half_b - sqrt(disc)) / a;
	if (*t < EPSILON)
		*t = (-half_b + sqrt(disc)) / a;
	return (*t >= EPSILON);
}

static t_color	get_sphere_checkerboard(t_uv uv)
{
	int		u;
	int		v;

	u = floor(uv.u * 10.0);
	v = floor(uv.v * 10.0);
	if ((u + v) % 2 == 0)
		return ((t_color){255, 255, 255});
	return ((t_color){0, 0, 0});
}

static void	apply_sphere_texture(t_spheres *sp, t_vector3 *normal,
		t_color *color, t_vector3 p)
{
	t_uv	uv;

	if (sp->bump_map || sp->albedo_map || sp->checkerboard)
	{
		uv = sphere_uv(p, sp->center);
		if (sp->bump_map)
			*normal = perturb_normal(*normal, sp->bump_map, uv);
		if (sp->checkerboard)
			*color = get_sphere_checkerboard(uv);
		if (sp->albedo_map)
			*color = sample_texture_color(sp->albedo_map, uv);
		else if (sp->bump_map)
			*color = sample_texture_color(sp->bump_map, uv);
	}
}

int	intersect_sphere(t_ray ray, t_spheres *sphere, t_hit *hit)
{
	t_variables	var;
	t_vector3	normal;
	t_color		final_color;

	if (!solve_sphere_quadratic(ray, sphere, &var.t))
		return (0);
	if (!is_closer_hit(hit, var.t))
		return (0);
	var.hit_point = ray_at(ray, var.t);
	normal = sphere_normal(var.hit_point, sphere->center);
	final_color = sphere->color;
	apply_sphere_texture(sphere, &normal, &final_color, var.hit_point);
	if (vec_dot(normal, ray.direction) > 0)
		normal = vec_scale(normal, -1);
	var.hit = hit;
	update_hit(&var, normal, final_color);
	hit->object = sphere;
	hit->type = SP;
	hit->shininess = sphere->shininess;
	return (1);
}
