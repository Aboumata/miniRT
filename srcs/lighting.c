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
	t_color		black;
	double		distance;
	double		intensity;

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

static t_color calculate_specular(t_hit *hit, t_light *light, t_vector3 view_dir)
{
	t_vector3 light_dir;
	t_vector3 to_light;
	t_vector3 reflect_dir;
	double spec_intensity;
	double spec_dot;
	t_color result;

	to_light = vec_sub(light->pos, hit->point);
	light_dir = vec_normalize(to_light);

	reflect_dir = vec_reflect(light_dir, hit->normal);
	spec_dot = vec_dot(reflect_dir, view_dir);

	static int printed = 0;
	if (!printed && hit->type == SP) {
	    printf("\n=== SPECULAR DEBUG ===\n");
	    printf("Shininess: %f\n", hit->shininess);
	    printf("Light dir: (%f, %f, %f)\n", light_dir.x, light_dir.y, light_dir.z);
	    printf("View dir: (%f, %f, %f)\n", view_dir.x, view_dir.y, view_dir.z);
	    printf("Reflect dir: (%f, %f, %f)\n", reflect_dir.x, reflect_dir.y, reflect_dir.z);
	    printf("Spec dot: %f\n", spec_dot);
	    printed = 1;
	}

	if (spec_dot < 0)
		spec_dot = 0;

	spec_intensity = pow(spec_dot, hit->shininess);
	spec_intensity *= light->ratio;

	printf("Spec intensity: %f\n", spec_intensity);

	result.r = (int)(255 * spec_intensity);
	result.g = (int)(255 * spec_intensity);
	result.b = (int)(255 * spec_intensity);

	return (result);
}

t_color	calculate_lighting(t_hit *hit, t_scene *scene)
{
	t_color	final_color;
	t_color	ambient;
	t_color	diffuse;
	t_color specular;
	t_light	*light;
	t_vector3 view_dir;

	view_dir = vec_sub(scene->camera.pos, hit->point);
	view_dir = vec_normalize(view_dir);

	ambient = calculate_ambient(scene->ambient, hit->color);
	final_color = ambient;

	light = scene->light;
	while (light)
	{
		diffuse = calculate_diffuse(hit, light, scene);
		final_color = color_add(final_color, diffuse);
		if (hit->shininess > 0)
		{
			specular = calculate_specular(hit, light, view_dir);
			final_color = color_add(final_color, specular);
		}
		light = light->next;
	}
	return (final_color);
}
