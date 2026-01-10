/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:04:32 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/09 19:04:41 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vector3	vec_add(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector3	vec_sub(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector3	vec_scale(t_vector3 v, double scale)
{
	t_vector3	result;

	result.x = v.x * scale;
	result.y = v.y * scale;
	result.z = v.z * scale;
	return (result);
}

double	vec_length(t_vector3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
