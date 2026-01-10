/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:24:00 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/09 18:31:14 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_color	color_multiply(t_color a, t_color b)
{
	t_color	result;

	result.r = (a.r * b.r) / 255;
	result.g = (a.g * b.g) / 255;
	result.b = (a.b * b.b) / 255;
	return (result);
}

t_color	color_scale(t_color color, double ratio)
{
	t_color	result;

	result.r = (int)(color.r * ratio);
	result.g = (int)(color.g * ratio);
	result.b = (int)(color.b * ratio);
	return (result);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r + b.r;
	result.g = a.g + b.g;
	result.b = a.b + b.b;
	if (result.r > 255)
		result.r = 255;
	if (result.g > 255)
		result.g = 255;
	if (result.b > 255)
		result.b = 255;
	return (result);
}

t_color	calculate_ambient(t_ambient ambient, t_color obj_color)
{
	t_color	result;

	result = color_multiply(obj_color, ambient.color);
	result = color_scale(result, ambient.ratio);
	return (result);
}
