/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:57:01 by abdahman          #+#    #+#             */
/*   Updated: 2025/10/16 18:01:51 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_plan(t_scene *scene, char **token)
{
	t_planes	*plane;

	if (count_tokens(token) != 4 && count_tokens(token) != 5)
	{
		write(2, "Error: invalid plan\n", 20);
		exit(1);
	}
	plane = ft_malloc(sizeof(t_planes), &(scene->mem));
	plane->point = parse_vec(token[1]);
	plane->color = parse_color(token[3]);
	plane->normal = parse_vec(token[2]);
	if (!is_normalized(plane->normal))
	{
		write(2, "Error: plan not normalized\n", 27);
		exit(1);
	}
	if (count_tokens(token) == 5)
	{
		plane->shininess = ft_atof(token[4]);
		if (plane->shininess < 0)
			exit((perror("Error: shininess should be non-negative\n"), 1));
	}
	else
		plane->shininess = 0.0;
	add_obj(scene, plane, PL);
}
