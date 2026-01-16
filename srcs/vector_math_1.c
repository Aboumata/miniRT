/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 04:02:38 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/09 19:05:39 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vector3	vec_normalize(t_vector3 v)
{
	double		length;
	t_vector3	result;

	length = vec_length(v);
	if (length == 0)
		return (v);
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;
	return (result);
}

double	vec_dot(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector3	vec_cross(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vector3	vec_reflect(t_vector3 v, t_vector3 n)
{
	t_vector3	reflection;
	double		dot;

	dot = vec_dot(v, n);
	reflection = vec_sub(v, vec_scale(n, 2.0 * dot));
	return (reflection);
}
