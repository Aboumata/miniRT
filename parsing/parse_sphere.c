/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:46:20 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/16 11:20:00 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	check_sphere_token_count(t_scene *scene, char **token, int count)
{
	if (count < 4 || count > 6)
		ft_perror(token, scene, "Error: invalid sphere\n");
}

static void	set_sphere_defaults(t_spheres *sphere)
{
	sphere->shininess = 0.0;
	sphere->bump_map = NULL;
	sphere->albedo_map = NULL;
}

static void	parse_sphere_extras(t_scene *scene, char **token,
			t_spheres *sphere, int count)
{
	if (count >= 5)
	{
		sphere->shininess = ft_atof(token[4], NULL);
		if (sphere->shininess < 0)
			ft_perror(token, scene,
				"Error: shininess should be non-negative\n");
	}
	if (count == 6 && token[5][0] != '\0')
	{
		sphere->bump_map = load_texture(token[5], scene->mlx, &scene->mem);
		if (!sphere->bump_map)
			ft_perror(token, scene, NULL);
	}
}

void	parse_sphere(t_scene *scene, char **token)
{
	t_spheres	*sphere;
	int			count;

	count = count_tokens(token);
	check_sphere_token_count(scene, token, count);
	sphere = ft_malloc(sizeof(t_spheres), &(scene->mem));
	sphere->center = parse_vec(token, 1, scene);
	sphere->diameter = ft_atof(token[2], NULL);
	if (sphere->diameter < 0)
		ft_perror(token, scene, "Error: diameter should be positive\n");
	sphere->color = parse_color(token, 3, scene);
	set_sphere_defaults(sphere);
	parse_sphere_extras(scene, token, sphere, count);
	add_obj(scene, sphere, SP);
}
