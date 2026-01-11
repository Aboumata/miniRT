/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:04:46 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/11 14:55:43 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	ft_continue(t_variables *var, t_triangle *triangle)
{
	t_vector3	hit_point;
	t_vector3	normal;

	if (var->t < EPSILON || var->t > var->hit->t)
		return (0);
	hit_point = ray_at(var->ray, var->t);
	normal = vec_cross(var->edgs[0], var->edgs[1]);
	normal = vec_normalize(normal);
	update_hit(var, normal, triangle->color);
	var->hit->object = triangle;
	var->hit->type = TRIANGLE;
	return (1);
}

int	intersect_triangle(t_ray ray, t_triangle *triangle, t_hit *hit)
{
	t_variables	var;
	t_vector3	p;
	t_vector3	s;
	t_vector3	q;

	double (u), v, det, inv_det;
	var.hit = hit;
	var.edgs[0] = vec_sub(triangle->p2, triangle->p1);
	var.edgs[1] = vec_sub(triangle->p3, triangle->p1);
	p = vec_cross(ray.direction, var.edgs[1]);
	det = vec_dot(var.edgs[0], p);
	if (fabs(det) < EPSILON)
		return (0);
	inv_det = 1.0 / det;
	s = vec_sub(ray.origin, triangle->p1);
	u = inv_det * vec_dot(s, p);
	if (u < 0.0 || u > 1.0)
		return (0);
	q = vec_cross(s, var.edgs[0]);
	v = inv_det * vec_dot(ray.direction, q);
	if (v < 0.0 || u + v > 1.0)
		return (0);
	var.t = inv_det * vec_dot(var.edgs[1], q);
	return (ft_continue(&var, triangle));
}
