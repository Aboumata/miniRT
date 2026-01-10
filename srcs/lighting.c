/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:32:14 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/09 18:30:52 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static t_color	calculate_diffuse(t_hit *hit, t_light *light, t_scene *scene)
{
	t_vector3	light_dir;
	t_vector3	to_light;
	t_color		result;
	t_color		black;

	double (distance), intensity;
	to_light = vec_sub(light->pos, hit->point);
	distance = vec_length(to_light);
	(void)distance;
	light_dir = vec_normalize(to_light);
	if (is_in_shadow(hit->point, hit->normal, light->pos, scene))
	{
		black.r = 0;
		black.g = 0;
		black.b = 0;
		return (black);
	}
	intensity = vec_dot(hit->normal, light_dir);
	if (intensity < 0)
		intensity = 0;
	result = color_multiply(hit->color, light->color);
	result = color_scale(result, intensity * light->ratio);
	return (result);
}

static t_color	calculate_specular(t_hit *hit, t_light *light,
									t_vector3 view_dir)
{
	t_vector3	light_dir;
	t_vector3	to_light;
	t_vector3	reflect_dir;
	t_color		result;

	double (spec_intensity), spec_dot;
	to_light = vec_sub(light->pos, hit->point);
	light_dir = vec_normalize(to_light);
	reflect_dir = vec_reflect(vec_scale(light_dir, -1), hit->normal);
	spec_dot = vec_dot(reflect_dir, view_dir);
	if (spec_dot < 0)
		spec_dot = 0;
	spec_intensity = pow(spec_dot, hit->shininess);
	spec_intensity *= light->ratio;
	if (spec_intensity > 1.0)
		spec_intensity = 1.0;
	result.r = (int)(255 * spec_intensity);
	result.g = (int)(255 * spec_intensity);
	result.b = (int)(255 * spec_intensity);
	return (result);
}

t_color	calculate_lighting(t_hit *hit, t_scene *scene)
{
	t_color		final_color;
	t_color		ambient;
	t_color		diffuse_specular[2];
	t_light		*light;
	t_vector3	view_dir;

	view_dir = vec_sub(scene->camera.pos, hit->point);
	view_dir = vec_normalize(view_dir);
	ambient = calculate_ambient(scene->ambient, hit->color);
	final_color = ambient;
	light = scene->light;
	while (light)
	{
		diffuse_specular[0] = calculate_diffuse(hit, light, scene);
		final_color = color_add(final_color, diffuse_specular[0]);
		if (hit->shininess > 0)
		{
			diffuse_specular[1] = calculate_specular(hit, light, view_dir);
			final_color = color_add(final_color, diffuse_specular[1]);
		}
		light = light->next;
	}
	return (final_color);
}
