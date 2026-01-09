/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 15:04:46 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/09 09:59:58 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	ft_continue(double t, t_hit *hit, t_ray ray, t_triangle *triangle,
					t_vector3 edgs[2])
{
	t_vector3	hit_point;
	t_vector3	normal;

	if (t < EPSILON || t > hit->t)
		return (0);
	hit_point = ray_at(ray, t);
	normal = vec_cross(edgs[0], edgs[1]);
	normal = vec_normalize(normal);
	update_hit(hit, t, hit_point, normal, triangle->color);
	hit->object = triangle;
	hit->type = TRIANGLE;
	return (1);
}
int	intersect_triangle(t_ray ray, t_triangle *triangle, t_hit *hit)
{
	t_vector3	edgs[2];
	t_vector3	p;
	t_vector3	s;
	t_vector3	q;

	double (u), v, det, inv_det, t;
	edgs[0] = vec_sub(triangle->p2, triangle->p1);
	edgs[1] = vec_sub(triangle->p3, triangle->p1);
	p = vec_cross(ray.direction, edgs[1]);
	det = vec_dot(edgs[0], p);
	if (fabs(det) < EPSILON)
		return (0);
	inv_det = 1.0 / det;
	s = vec_sub(ray.origin, triangle->p1);
	u = inv_det * vec_dot(s, p);
	if (u < 0.0 || u > 1.0)
		return (0);
	q = vec_cross(s, edgs[0]);
	v = inv_det * vec_dot(ray.direction, q);
	if (v < 0.0 || u + v > 1.0)
		return (0);
	t = inv_det * vec_dot(edgs[1], q);
	return (ft_continue(t, hit, ray, triangle, edgs));
}
