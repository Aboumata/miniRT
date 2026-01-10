/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:57:01 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/09 19:24:37 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	ft_continue(t_planes *plane, char **token, int c)
{
	if (c >= 5)
	{
		if (!ft_strcmp(token[4], "cb"))
			plane->checkerboard = 1;
		else
		{
			plane->shininess = ft_atof(token[4]);
			if (plane->shininess < 0)
				exit((perror("Error: shininess should be non-negative"), 1));
		}
	}
	if (c == 6)
	{
		if (ft_strcmp(token[5], "cb"))
			exit((perror("Error: invalid flag"), 1));
		plane->checkerboard = 1;
	}
}

void	parse_plan(t_scene *scene, char **token)
{
	t_planes	*plane;
	int			c;

	c = count_tokens(token);
	if (c < 4 || c > 6)
	{
		write(2, "Error: invalid plan\n", 20);
		exit(1);
	}
	plane = ft_malloc(sizeof(t_planes), &(scene->mem));
	plane->point = parse_vec(token[1]);
	plane->normal = parse_vec(token[2]);
	plane->color = parse_color(token[3]);
	if (!is_normalized(plane->normal))
	{
		write(2, "Error: plan not normalized\n", 27);
		exit(1);
	}
	plane->shininess = 0.0;
	plane->checkerboard = 0;
	ft_continue(plane, token, c);
	add_obj(scene, plane, PL);
}
