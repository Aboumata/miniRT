/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniRT                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14                                   #+#    #+#             */
/*   Updated: 2026/01/14                                   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static double	wrap01(double x)
{
	x = x - floor(x);
	if (x < 0.0)
		x += 1.0;
	return (x);
}

static double	clamp01(double x)
{
	if (x < 0.0)
		return (0.0);
	if (x > 1.0)
		return (1.0);
	return (x);
}

static double	clamp(double x, double a, double b)
{
	if (x < a)
		return (a);
	if (x > b)
		return (b);
	return (x);
}

/*
** Frisvad basis (stable, no "ring seam" from axis switching)
*/
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

t_vector3	perturb_normal(t_vector3 normal, t_texture *bump, t_uv uv)
{
	t_vector3	t;
	t_vector3	b;
	t_vector3	p;
	double		du;
	double		dv;
	double		hr;
	double		hl;
	double		hu;
	double		hd;
	double		dhdu;
	double		dhdv;
	double		strength;
	double		pole;

	if (!bump || bump->width < 2 || bump->height < 2)
		return (normal);
	normal = vec_normalize(normal);
	uv.u = wrap01(uv.u);
	uv.v = clamp01(uv.v);

	du = 1.0 / (double)bump->width;
	dv = 1.0 / (double)bump->height;

	hr = get_bump_height(bump, wrap01(uv.u + du), uv.v);
	hl = get_bump_height(bump, wrap01(uv.u - du), uv.v);
	hu = get_bump_height(bump, uv.u, clamp01(uv.v + dv));
	hd = get_bump_height(bump, uv.u, clamp01(uv.v - dv));

	/* centered differences (no crazy scaling) */
	dhdu = 0.5 * (hr - hl);
	dhdv = 0.5 * (hu - hd);

	/* clamp slope to prevent flipped normals / shadow acne */
	dhdu = clamp(dhdu, -0.6, 0.6);
	dhdv = clamp(dhdv, -0.6, 0.6);

	/* reduce bump near poles (UV compression on spheres) */
	pole = sin(PI * uv.v);
	pole = clamp01(pole);

	build_basis(normal, &t, &b);

	/* start small; raise slowly if you want more */
	strength = 1.5 * (0.3 + 0.7 * pole);  // Very pronounced bumps

	p = normal;
	p = vec_add(p, vec_scale(t, dhdu * strength));
	p = vec_add(p, vec_scale(b, dhdv * strength));
	p = vec_normalize(p);

	/* keep same hemisphere as geometric normal */
	if (vec_dot(p, normal) < 0.0)
		p = vec_scale(p, -1.0);
	/* if still too far, fall back (prevents extreme artifacts) */
	if (vec_dot(p, normal) < 0.2)
		return (normal);
	return (p);
}
