/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:46:20 by abdahman          #+#    #+#             */
/*   Updated: 2025/10/16 17:47:57 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void parse_sphere(t_scene *scene, char **token)
{
	t_spheres *sphere;

	if (count_tokens(token) != 4)
		exit((perror("Error: invalid sphere\n"), 1));
	sphere = ft_malloc(sizeof(t_spheres), &(scene->mem));
	sphere->center = parse_vec(token[1]);
	sphere->diameter = ft_atof(token[2]);
	if (sphere->diameter < 0)
		exit((perror("Error: diameter should be positif"), 1));
	sphere->color = parse_color(token[3]);
	add_obj(scene, sphere, SP);
}
