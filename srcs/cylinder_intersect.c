/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:33:14 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/09 19:24:07 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

// PART1
/*
 *Ray: P(t) = ray.origin + t × ray.direction
 *
 *We want: distance from P(t) to axis = radius
 *
 *Let:
 *  oc = ray.origin - cylinder.center
 *  axis = cylinder.axis (normalized)
 *
 *Step 1: Project oc onto asxi
 *  oc_proj = (oc · axis) × axis
 *
 *Step 2: Get perpendicular component
 *  oc_perp = oc - oc_proj
 *
 *Step 3: Do same for ray direction
 *  dir_proj = (ray.direction · axis) × axis
 *  dir_perp = ray.direction - dir_proj
 *
 *Step 4: Perpendicular distance equation becomes:
 *  |oc_perp + t × dir_perp|² = radius²
 *
 *Step 5: Expand (this is a quadratic equation!):
 *  a = dir_perp · dir_perp
 *  b = 2 × (oc_perp · dir_perp)
 *  c = oc_perp · oc_perp - radius²
 *
 *Step 6: Solve using quadratic formula
 *  discriminant = b² - 4ac
 *  t = (-b ± √discriminant) / 2a
 */

// PART2
/*
 *1. Calculate hit point: P = ray.origin + t × ray.direction
 *2. Project hit point onto axis: h = (P - center) · axis
 *3. Check if h is within bounds:
 *   - Top limit: h <= height / 2
 *   - Bottom limit: h >= -height / 2
 *
 *If outside bounds: reject this hit, try caps instead
 */

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
	t_vector3	cap_center;
	t_vector3	to_cap;
	t_vector3	to_hit;
	t_vector3	hit_point;
	t_vector3	normal;

	double (t), found_hit = 0.0, radius = cy->diameter / 2.0, dist_sq,
	half_height = cy->height / 2.0, denom = vec_dot(ray.direction, cy->dir);
	if (fabs(denom) > EPSILON)
	{
		cap_center = vec_add(cy->center, vec_scale(cy->dir, half_height));
		to_cap = vec_sub(cap_center, ray.origin);
		t = vec_dot(to_cap, cy->dir) / denom;
		if (is_closer_hit(hit, t))
		{
			hit_point = ray_at(ray, t);
			to_hit = vec_sub(hit_point, cap_center);
			dist_sq = vec_dot(to_hit, to_hit);
			if (dist_sq <= radius * radius)
			{
				normal = cy->dir;
				update_hit(hit, t, hit_point, normal, cy->color);
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
		t = vec_dot(to_cap, cy->dir) / denom;
		if (is_closer_hit(hit, t))
		{
			hit_point = ray_at(ray, t);
			to_hit = vec_sub(hit_point, cap_center);
			dist_sq = vec_dot(to_hit, to_hit);
			if (dist_sq <= radius * radius)
			{
				normal = vec_scale(cy->dir, -1.0);
				update_hit(hit, t, hit_point, normal, cy->color);
				hit->object = cy;
				hit->type = CY;
				hit->shininess = cy->shininess;
				found_hit = 1;
			}
		}
	}
	return (found_hit);
}

static int	intersect_cylinder_body(t_ray ray, t_cylinders *cylinder,
				t_hit *hit)
{
	t_vector3	oc;
	t_vector3	oc_perp;
	t_vector3	dir_perp;
	t_vector3	hit_point;
	t_vector3	to_hit;
	t_vector3	normal;

	double (a), radius = cylinder->diameter / 2.0, discriminant, t, b, c;
	double (half_height), height_on_dir, dir_dot_dir, oc_dot_dir;
	oc = vec_sub(ray.origin, cylinder->center);
	half_height = cylinder->height / 2.0;
	oc_dot_dir = vec_dot(oc, cylinder->dir);
	oc_perp = vec_sub(oc, vec_scale(cylinder->dir, oc_dot_dir));
	dir_dot_dir = vec_dot(ray.direction, cylinder->dir);
	dir_perp = vec_sub(ray.direction, vec_scale(cylinder->dir, dir_dot_dir));
	a = vec_dot(dir_perp, dir_perp);
	b = 2.0 * vec_dot(oc_perp, dir_perp);
	c = vec_dot(oc_perp, oc_perp) - (radius * radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (!is_closer_hit(hit, t))
		return (0);
	hit_point = ray_at(ray, t);
	to_hit = vec_sub(hit_point, cylinder->center);
	height_on_dir = vec_dot(to_hit, cylinder->dir);
	if (height_on_dir < -half_height || height_on_dir > half_height)
		return (0);
	normal = cylinder_body_normal(hit_point, cylinder);
	update_hit(hit, t, hit_point, normal, cylinder->color);
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
