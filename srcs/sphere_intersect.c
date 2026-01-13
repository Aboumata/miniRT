/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:32:47 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 16:04:47 by abdahman         ###   ########.fr       */
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

double	help(double t, double sqrt_d, double half_b, double a)
{
	if (a < EPSILON)
		return (0);
	t = (-half_b - sqrt_d) / a;
	if (t < EPSILON)
		t = (-half_b + sqrt_d) / a;
	return (t);
}

int	intersect_sphere(t_ray ray, t_spheres *sphere, t_hit *hit)
{
	t_variables	var;
	t_vector3	normal;
	t_uv		uv;
	double		a;
	double		sqrt_d;
	double		radius;
	double		t;
	double		half_b;
	double		c;
	double		discriminant;

	t = 0.0;
	var.hit = hit;
	var.oc = vec_sub(ray.origin, sphere->center);
	a = vec_dot(ray.direction, ray.direction);
	half_b = vec_dot(var.oc, ray.direction);
	radius = sphere->diameter / 2.0;
	c = vec_dot(var.oc, var.oc) - (radius * radius);
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	sqrt_d = sqrt(discriminant);
	t = help(t, sqrt_d, half_b, a);
	if (t < EPSILON || t > hit->t)
		return (0);
	var.hit_point = ray_at(ray, t);
	var.t = t;
	normal = sphere_normal(var.hit_point, sphere->center);
	if (sphere->bump_map)
	{
		uv = sphere_uv(var.hit_point, sphere->center);
		normal = perturb_normal(normal, sphere->bump_map, uv);
	}
	if (vec_dot(normal, ray.direction) > 0)
		normal = vec_scale(normal, -1);
	update_hit(&var, normal, sphere->color);
	hit->normal = normal;
	hit->object = sphere;
	hit->type = SP;
	hit->shininess = sphere->shininess;
	return (1);
}
