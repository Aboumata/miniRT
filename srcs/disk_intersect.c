/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 10:32:37 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/11 14:52:01 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	intersect_disk(t_ray ray, t_disk *disk, t_hit *hit)
{
	t_vector3	normal;
	t_variables	var;
	t_vector3	p_to_center;

	double (numer), denom, r;
	normal = disk->normal;
	var.hit = hit;
	denom = vec_dot(ray.direction, normal);
	if (fabs(denom) < EPSILON)
		return (0);
	if (denom > 0)
		normal = vec_scale(normal, -1);
	var.oc = vec_sub(disk->center, ray.origin);
	numer = vec_dot(var.oc, normal);
	var.t = numer / denom;
	if (var.t < EPSILON || var.t > var.hit->t)
		return (0);
	var.hit_point = ray_at(ray, var.t);
	p_to_center = vec_sub(var.hit_point, disk->center);
	r = disk->diameter / 2;
	if (vec_dot(p_to_center, p_to_center) > r * r)
		return (0);
	update_hit(&var, normal, disk->color);
	hit->object = disk;
	return (hit->type = DISK, 1);
}
