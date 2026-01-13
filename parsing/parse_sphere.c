/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:46:20 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/11 22:45:00 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_sphere(t_scene *scene, char **token)
{
	t_spheres	*sphere;
	int			count;

	count = count_tokens(token);
	if (count < 4 || count > 6)
		ft_perror(token, scene, "Error: invalid sphere\n");
	sphere = ft_malloc(sizeof(t_spheres), &(scene->mem));
	sphere->center = parse_vec(token, 1, scene);
	sphere->diameter = ft_atof(token[2], NULL);
	if (sphere->diameter < 0)
		ft_perror(token, scene, "Error: diameter should be positive\n");
	sphere->color = parse_color(token, 3, scene);
	sphere->shininess = 0.0;
	sphere->bump_map = NULL;
	if (count >= 5)
	{
		sphere->shininess = ft_atof(token[4], NULL);
		if (sphere->shininess < 0)
			ft_perror(token, scene,
				"Error: shininess should be non-negative\n");
	}
	if (count == 6)
		sphere->bump_map = load_texture(token[5], scene->mlx, &scene->mem);
	add_obj(scene, sphere, SP);
}
