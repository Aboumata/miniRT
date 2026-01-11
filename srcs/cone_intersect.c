/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 08:43:03 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/11 16:46:21 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
	(P - C) · V = ||P - C|| cos(θ) <- cone
	--- P = O + D.t 			   <- cho3a3
	ba3d ta3wid wa al hisab .. :
	        (m = tan(..)^2)
	$ a = D.D - (1 + m) * (D.V)^2
	(D.V)^2 = (D.V).(D.V)
	$ half_b = D.W - (1 + m) * (D.V * W.V)
	$ c = W.W - (1 + m) * (W.V)^2
	normal ..
	P = hit point, C = apex, V = axis 
	m = dot(P - C, V);
	k = 1.0 + tan2;
	N = normalize( (P - C) - (k * m) * V );
*/

static int	check_cone_height(t_variables *var, t_ray ray, t_cone *cone, double tan2)
{
	t_vector3	normal;
	t_vector3	pc;

	double		(h), m, k;
	if (var->t < EPSILON || var->t > var->hit->t)
		return (0);
	h = vec_dot(vec_sub(vec_add(ray.origin, vec_scale(ray.direction, var->t)),
				cone->center), cone->dir);
	if (h < 0 || h > cone->height)
		return (0);
	var->t = var->t;
	var->hit_point = vec_add(ray.origin, vec_scale(ray.direction, var->t));
	pc = vec_sub(var->hit_point, cone->center);
	m = vec_dot(pc, cone->dir);
	k = 1.0 + tan2;
	normal = vec_normalize(vec_sub(pc, vec_scale(cone->dir, k * m)));
	update_hit(var, normal, cone->color);
	return (1);
}

int	intersect_cone(t_ray ray, t_cone *cone, t_hit *hit)
{
	t_variables	var;

	double (a), r = cone->diameter / 2.0, half_b, c, delta, sqrt_d,
	tan2 = (r * r) / (cone->height * cone->height), dv, wv;
	var.hit = hit;
	var.oc = vec_sub(ray.origin, cone->center);
	dv = vec_dot(ray.direction, cone->dir);
	wv = vec_dot(var.oc, cone->dir);
	a = vec_dot(ray.direction, ray.direction) - (1.0 + tan2) * (dv * dv);
	if (fabs(a) < EPSILON)
		return (0);
	half_b = vec_dot(ray.direction, var.oc) - (1.0 + tan2) * (dv * wv);
	c = vec_dot(var.oc, var.oc) - (1.0 + tan2) * (wv * wv);
	delta = (half_b * half_b) - (a * c);
	if (delta < 0)
		return (0);
	sqrt_d = sqrt(delta);
	var.t = (-half_b - sqrt_d) / a;
	if (var.t < EPSILON || var.t > hit->t)
		var.t = (-half_b + sqrt_d) / a;
	return (check_cone_height(&var, ray, cone, tan2));
}
