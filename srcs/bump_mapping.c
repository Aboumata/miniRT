/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:00:00 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static t_vector3	create_tangent(t_vector3 normal)
{
	t_vector3	tangent;
	t_vector3	up;

	up.x = 0;
	up.y = 1;
	up.z = 0;
	if (fabs(normal.y) > 0.9)
	{
		up.x = 1;
		up.y = 0;
		up.z = 0;
	}
	tangent = vec_cross(normal, up);
	tangent = vec_normalize(tangent);
	return (tangent);
}

t_vector3	perturb_normal(t_vector3 normal, t_texture *bump, t_uv uv)
{
	t_vector3	tangent;
	t_vector3	bitangent;
	t_vector3	perturbed;
	double		h_u;
	double		h_v;
	double		du;
	double		dv;
	double		strength;

	if (!bump || !bump->data || bump->width <= 0 || bump->height <= 0)
		return (normal);
	du = 1.0 / (double)bump->width;
	dv = 1.0 / (double)bump->height;
	strength = 0.3;
	h_u = get_bump_height(bump, uv.u + du, uv.v);
	h_u -= get_bump_height(bump, uv.u - du, uv.v);
	h_v = get_bump_height(bump, uv.u, uv.v + dv);
	h_v -= get_bump_height(bump, uv.u, uv.v - dv);
	tangent = create_tangent(normal);
	bitangent = vec_cross(normal, tangent);
	bitangent = vec_normalize(bitangent);
	perturbed = normal;
	perturbed = vec_add(perturbed, vec_scale(tangent, h_u * strength));
	perturbed = vec_add(perturbed, vec_scale(bitangent, h_v * strength));
	perturbed = vec_normalize(perturbed);
	return (perturbed);
}
