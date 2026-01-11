/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:33:36 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 14:53:36 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
 * Ray: p(t) = origin + t * direction
 * Plane: (P - plane_point) * normal = 0
 *
 * SOLVE!
 *
 * (origin + t * direction - plane_point) * normal = 0;
 * normal * origin + t * (direction * normal) - plane_point * normal = 0
 * t * (direction * normal) = plane_point * normal - normal * origin
 * t * (direction * normal) = normal * (plane_point - origin)
 * t = normal * (plane_point - origin) / (direction * normal)
 *
 */

t_color	update_color(int r, int g, int b, t_color color)
{
	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

void	checkerboard(t_vector3 hit_p, t_planes *pl)
{
	float	size;
	int		x;
	int		y;
	int		z;

	if (!pl->checkerboard)
		return ;
	size = 1 / 10.0;
	x = floor(hit_p.x) * size;
	z = floor(hit_p.z) * size;
	y = floor(hit_p.y) * size;
	if ((x + y + z) % 2 == 0)
		pl->color = update_color(255, 255, 255, pl->color);
	else
		pl->color = update_color(0, 0, 0, pl->color);
}

int	intersect_plane(t_ray ray, t_planes *plane, t_hit *hit)
{
	t_vector3	to_plane;
	t_variables	var;
	t_vector3	normal;

	double (denom), numer;
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
	checkerboard(var.hit_point, plane);
	update_hit(&var, normal, plane->color);
	hit->object = plane;
	hit->type = PL;
	hit->shininess = plane->shininess;
	return (1);
}
