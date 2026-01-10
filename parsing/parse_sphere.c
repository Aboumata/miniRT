/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:46:20 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/10 22:37:28 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_sphere(t_scene *scene, char **token)
{
	t_spheres	*sphere;
	int			check;

	check = 0;
	if (count_tokens(token) != 4 && count_tokens(token) != 5)
		ft_perror("Error: invalid sphere\n", token);
	sphere = ft_malloc(sizeof(t_spheres), &(scene->mem));
	sphere->center = parse_vec(token, 1);
	sphere->diameter = ft_atof(token[2], &check);
	if (sphere->diameter < 0)
		ft_perror("Error: diameter should be positive\n", token);
	sphere->color = parse_color(token, 3);
	if (count_tokens(token) == 5)
	{
		sphere->shininess = ft_atof(token[4], &check);
		if (sphere->shininess < 0)
			ft_perror("Error: shininess should be non-negative\n", token);
	}
	else
		sphere->shininess = 0.0;
	add_obj(scene, sphere, SP);
}
