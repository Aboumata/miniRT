/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:57:01 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/15 16:16:42 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	ft_continue(t_planes *plane, char **token, int c, t_scene *scene)
{
	if (c >= 5)
	{
		if (!ft_strcmp(token[4], "cb"))
			plane->checkerboard = 1;
		else
		{
			plane->shininess = ft_atof(token[4], NULL);
			if (plane->shininess < 0)
				return (0);
		}
	}
	if (c >= 6)
	{
		if (!ft_strcmp(token[5], "cb"))
			plane->checkerboard = 1;
		else if (c == 6 && token[5][0] != '\0')
			// plane->bump_map = load_texture(token[5], scene->mlx, &scene->mem);
			plane->albedo_map = load_texture(token[5], scene->mlx, &scene->mem);
	}
	if (c == 7)
	{
		if (token[6][0] != '\0')
			plane->bump_map = load_texture(token[6], scene->mlx, &scene->mem);
	}
	return (1);
}

void	parse_plan(t_scene *scene, char **token)
{
	t_planes	*plane;
	int			c;

	c = count_tokens(token);
	if (c < 4 || c > 7)
	{
		write(2, "Error: invalid plan\n", 20);
		exit((free_split(token), 1));
	}
	plane = ft_malloc(sizeof(t_planes), &(scene->mem));
	plane->point = parse_vec(token, 1, scene);
	plane->normal = parse_vec(token, 2, scene);
	plane->color = parse_color(token, 3, scene);
	if (!is_normalized(plane->normal))
	{
		write(2, "Error: plan not normalized\n", 27);
		ft_perror(token, scene, NULL);
	}
	plane->shininess = 0.0;
	plane->checkerboard = 0;
	plane->albedo_map = NULL;
	plane->bump_map = NULL;
	if (!ft_continue(plane, token, c, scene))
		ft_perror(token, scene, "Error: invalid plan\n");
	add_obj(scene, plane, PL);
}
