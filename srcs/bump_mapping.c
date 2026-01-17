/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:35:47 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/17 09:39:57 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	build_basis(t_vector3 n, t_vector3 *t, t_vector3 *b)
{
	double	a;
	double	c;

	if (n.z < -0.9999999)
	{
		t->x = 0.0;
		t->y = -1.0;
		t->z = 0.0;
		b->x = -1.0;
		b->y = 0.0;
		b->z = 0.0;
		return ;
	}
	a = 1.0 / (1.0 + n.z);
	c = -n.x * n.y * a;
	t->x = 1.0 - n.x * n.x * a;
	t->y = c;
	t->z = -n.x;
	b->x = c;
	b->y = 1.0 - n.y * n.y * a;
	b->z = -n.y;
	*t = vec_normalize(*t);
	*b = vec_normalize(*b);
}

t_uv	adapt_uv(t_uv uv)
{
	uv.u = wrap01(uv.u);
	uv.v = clamp01(uv.v);
	uv.v = wrap01(uv.v);
	return (uv);
}

t_vector3	perturb_normal(t_vector3 normal, t_texture *bump, t_uv uv)
{
	t_vector3	t;
	t_vector3	b;
	t_vector3	p;

	if (!bump || bump->width < 2 || bump->height < 2)
		return (normal);
	uv = adapt_uv(uv);
	double (dhdv), hr, hl, hu, hd, dhdu, pole = clamp01(sin(PI * uv.v)),
	dv = 1.0 / (double)bump->height, du = 1.0 / (double)bump->width,
	strength = 1.5 * (0.3 + 0.7 * pole);
	normal = vec_normalize(normal);
	hr = get_bump_height(bump, wrap01(uv.u + du), uv.v);
	hl = get_bump_height(bump, wrap01(uv.u - du), uv.v);
	hu = get_bump_height(bump, uv.u, wrap01(uv.v + dv));
	hd = get_bump_height(bump, uv.u, wrap01(uv.v - dv));
	dhdu = clamp(0.5 * (hr - hl), -0.6, 0.6);
	dhdv = clamp(0.5 * (hu - hd), -0.6, 0.6);
	build_basis(normal, &t, &b);
	p = vec_add(normal, vec_scale(t, dhdu * strength));
	p = vec_normalize(vec_add(p, vec_scale(b, dhdv * strength)));
	if (vec_dot(p, normal) < 0.0)
		p = vec_scale(p, -1.0);
	if (vec_dot(p, normal) < 0.2)
		return (normal);
	return (p);
}
