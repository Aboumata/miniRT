/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
** Why your spheres look "bad":
** - Your old tangent basis had a hard switch when |normal.y| > 0.9.
**   That creates visible rings / seams on spheres.
** - Your sampling step was fixed (0.01). With 8x8 / 16x16 bump maps,
**   u +/- 0.01 often hits the SAME texel => h_u/h_v ~= 0 => weak/patchy bump.
**
** This version fixes both:
** 1) Stable orthonormal basis from the normal (Frisvad).
** 2) du/dv based on texture resolution + centered difference slope.
** 3) Wrap u, clamp v for neighbor sampling.
*/

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

/*
** Frisvad 2012 - Building an Orthonormal Basis, Revisited
** Given a unit normal n, compute tangent t and bitangent b.
** This avoids the "ring" artifact you got from switching reference axes.
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
	t_vector3	perturbed;
	double		du;
	double		dv;
	double		h_r;
	double		h_l;
	double		h_u;
	double		h_d;
	double		dhdu;
	double		dhdv;
	double		strength;

	if (!bump || bump->width < 2 || bump->height < 2)
		return (normal);
	normal = vec_normalize(normal);
	uv.u = wrap01(uv.u);
	uv.v = clamp01(uv.v);
	du = 1.0 / (double)bump->width;
	dv = 1.0 / (double)bump->height;
	h_r = get_bump_height(bump, wrap01(uv.u + du), uv.v);
	h_l = get_bump_height(bump, wrap01(uv.u - du), uv.v);
	h_u = get_bump_height(bump, uv.u, clamp01(uv.v + dv));
	h_d = get_bump_height(bump, uv.u, clamp01(uv.v - dv));
	dhdu = (h_r - h_l) / (2.0 * du);
	dhdv = (h_u - h_d) / (2.0 * dv);
	build_basis(normal, &t, &b);
	/*
	** Start small; for 8x8 maps slopes are big.
	** If you want stronger bump: try 0.10 -> 0.20
	*/
	strength = 0.08;
	perturbed = vec_add(normal, vec_scale(t, dhdu * strength));
	perturbed = vec_add(perturbed, vec_scale(b, dhdv * strength));
	return (vec_normalize(perturbed));
}
