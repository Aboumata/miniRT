/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:32:14 by aboumata          #+#    #+#             */
/*   Updated: 2025/11/09 21:32:15 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static t_color	color_multiply(t_color a, t_color b)
{
	t_color	result;

	result.r = (a.r * b.r) / 255;
	result.g = (a.g * b.g) / 255;
	result.b = (a.b * b.b) / 255;
	return (result);
}

static t_color	color_scale(t_color color, double ratio)
{
	t_color	result;

	result.r = (int)(color.r * ratio);
	result.g = (int)(color.g * ratio);
	result.b = (int)(color.b * ratio);
	return (result);
}

static t_color	color_add(t_color a, t_color b)
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

static t_color	calculate_ambient(t_ambient ambient, t_color obj_color)
{
	t_color	result;

	result = color_multiply(obj_color, ambient.color);
	result = color_scale(result, ambient.ratio);
	return (result);
}

static t_color	calculate_diffuse(t_hit *hit, t_light *light, t_scene *scene)
{
	t_vector3	light_dir;
	t_vector3	to_light;
	t_color		result;
	double		distance;
	double		intensity;

	(void)scene;
	to_light = vec_sub(light->pos, hit->point);
	distance = vec_length(to_light);
	(void)distance;
	light_dir = vec_normalize(to_light);
	intensity = vec_dot(hit->normal, light_dir);
	if (intensity < 0)
		intensity = 0;
	result = color_multiply(hit->color, light->color);
	result = color_scale(result, intensity * light->ratio);
	return (result);
}

t_color	calculate_lighting(t_hit *hit, t_scene *scene)
{
	t_color	final_color;
	t_color	ambient;
	t_color	diffuse;
	t_light	*light;

	ambient = calculate_ambient(scene->ambient, hit->color);
	final_color = ambient;
	light = scene->light;
	while (light)
	{
		diffuse = calculate_diffuse(hit, light, scene);
		final_color = color_add(final_color, diffuse);
		light = light->next;
	}
	return (final_color);
}
