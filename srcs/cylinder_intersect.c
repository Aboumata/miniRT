/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:33:14 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 21:59:34 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static t_vector3	cylinder_body_normal(t_vector3 hit_point,
		t_cylinders *cylinder)
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

static int	intersect_cylinder_caps(t_ray ray, t_cylinders *cy,
				t_hit *hit)
{
	t_variables	var;
	t_vector3	cap_center;
	t_vector3	to_cap;
	t_vector3	to_hit;
	t_vector3	normal;
	double		dist_sq;
	double		found_hit;
	double		radius;
	double		half_height;
	double		denom;

	found_hit = 0.0;
	radius = cy->diameter / 2.0;
	half_height = cy->height / 2.0;
	denom = vec_dot(ray.direction, cy->dir);
	ft_bzero(&var, sizeof(t_variables));
	var.hit = hit;
	if (fabs(denom) > EPSILON)
	{
		cap_center = vec_add(cy->center, vec_scale(cy->dir, half_height));
		to_cap = vec_sub(cap_center, ray.origin);
		var.t = vec_dot(to_cap, cy->dir) / denom;
		if (is_closer_hit(hit, var.t))
		{
			var.hit_point = ray_at(ray, var.t);
			to_hit = vec_sub(var.hit_point, cap_center);
			dist_sq = vec_dot(to_hit, to_hit);
			if (dist_sq <= radius * radius)
			{
				normal = cy->dir;
				update_hit(&var, normal, cy->color);
				hit->normal = normal;
				hit->object = cy;
				hit->type = CY;
				hit->shininess = cy->shininess;
				found_hit = 1;
			}
		}
	}
	if (fabs(denom) > EPSILON)
	{
		cap_center = vec_sub(cy->center, vec_scale(cy->dir, half_height));
		to_cap = vec_sub(cap_center, ray.origin);
		var.t = vec_dot(to_cap, cy->dir) / denom;
		if (is_closer_hit(hit, var.t))
		{
			var.hit_point = ray_at(ray, var.t);
			to_hit = vec_sub(var.hit_point, cap_center);
			dist_sq = vec_dot(to_hit, to_hit);
			if (dist_sq <= radius * radius)
			{
				normal = vec_scale(cy->dir, -1.0);
				update_hit(&var, normal, cy->color);
				hit->object = cy;
				hit->type = CY;
				hit->shininess = cy->shininess;
				found_hit = 1;
			}
		}
	}
	return ((int)found_hit);
}

static int	intersect_cylinder_body(t_ray ray, t_cylinders *cylinder,
				t_hit *hit)
{
	t_variables	var;
	t_vector3	oc_perp;
	t_vector3	dir_perp;
	t_vector3	to_hit;
	t_vector3	normal;
	t_uv		uv;
	double		a;
	double		radius;
	double		discriminant;
	double		b;
	double		c;
	double		half_height;
	double		height_on_dir;
	double		dir_dot_dir;
	double		oc_dot_dir;

	ft_bzero(&var, sizeof(t_variables));
	var.hit = hit;
	var.oc = vec_sub(ray.origin, cylinder->center);
	radius = cylinder->diameter / 2.0;
	half_height = cylinder->height / 2.0;
	oc_dot_dir = vec_dot(var.oc, cylinder->dir);
	oc_perp = vec_sub(var.oc, vec_scale(cylinder->dir, oc_dot_dir));
	dir_dot_dir = vec_dot(ray.direction, cylinder->dir);
	dir_perp = vec_sub(ray.direction, vec_scale(cylinder->dir, dir_dot_dir));
	a = vec_dot(dir_perp, dir_perp);
	b = 2.0 * vec_dot(oc_perp, dir_perp);
	c = vec_dot(oc_perp, oc_perp) - (radius * radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	var.t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (!is_closer_hit(hit, var.t))
		return (0);
	var.hit_point = ray_at(ray, var.t);
	to_hit = vec_sub(var.hit_point, cylinder->center);
	height_on_dir = vec_dot(to_hit, cylinder->dir);
	if (height_on_dir < -half_height || height_on_dir > half_height)
		return (0);
	normal = cylinder_body_normal(var.hit_point, cylinder);
	if (cylinder->bump_map)
	{
		uv = cylinder_uv(var.hit_point, cylinder);
		normal = perturb_normal(normal, cylinder->bump_map, uv);
	}
	if (vec_dot(normal, ray.direction) > 0)
		normal = vec_scale(normal, -1);
	update_hit(&var, normal, cylinder->color);
	hit->object = cylinder;
	hit->type = CY;
	hit->shininess = cylinder->shininess;
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
