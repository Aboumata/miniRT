/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:33:14 by aboumata          #+#    #+#             */
/*   Updated: 2025/11/09 21:33:16 by aboumata         ###   ########.fr       */
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
 *Step 1: Project oc onto axis
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
	t_vector3 v;
	t_vector3 projection;
	t_vector3 normal;
	double proj_length;

	v = vec_sub(hit_point, cylinder->center);
	proj_length = vec_dot(v, cylinder->dir);
	projection = vec_scale(cylinder->dir, proj_length);
	normal = vec_sub(v, projection);
	normal = vec_normalize(normal);

	return (normal);
}

static int intersect_cylinder_caps(t_ray ray, t_cylinders *cylinder, t_hit *hit)
{
	double half_height;
	double denom;
	t_vector3 top_center;


	half_height = cylinder->height / 2.0;
	top_center = vec_add(cylinder->center, vec_scale(cylinder->dir, half_height));


}