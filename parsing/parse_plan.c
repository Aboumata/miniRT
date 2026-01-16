/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:57:01 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/16 10:55:00 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	check_plan_token_count(int c, char **token)
{
	if (c < 4 || c > 7)
	{
		write(2, "Error: invalid plan\n", 20);
		exit((free_split(token), 1));
	}
}

static void	set_plan_defaults(t_planes *plane)
{
	plane->shininess = 0.0;
	plane->checkerboard = 0;
	plane->albedo_map = NULL;
	plane->bump_map = NULL;
}

static int	parse_plan_options(t_planes *plane, char **token, int c)
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
	if (c >= 6 && !ft_strcmp(token[5], "cb"))
		plane->checkerboard = 1;
	return (1);
}

static void	parse_plan_textures(t_scene *scene, t_planes *plane,
			char **token, int c)
{
	if (c == 6 && ft_strcmp(token[5], "cb") && token[5][0] != '\0')
	{
		plane->albedo_map = load_texture(token[5], scene->mlx, &scene->mem);
		if (!plane->albedo_map)
			ft_perror(token, scene, NULL);
	}
	if (c == 7 && token[6][0] != '\0')
	{
		plane->bump_map = load_texture(token[6], scene->mlx, &scene->mem);
		if (!plane->bump_map)
			ft_perror(token, scene, NULL);
	}
}

void	parse_plan(t_scene *scene, char **token)
{
	t_planes	*plane;
	int			c;

	c = count_tokens(token);
	check_plan_token_count(c, token);
	plane = ft_malloc(sizeof(t_planes), &(scene->mem));
	plane->point = parse_vec(token, 1, scene);
	plane->normal = parse_vec(token, 2, scene);
	plane->color = parse_color(token, 3, scene);
	if (!is_normalized(plane->normal))
	{
		write(2, "Error: plan not normalized\n", 27);
		ft_perror(token, scene, NULL);
	}
	set_plan_defaults(plane);
	if (!parse_plan_options(plane, token, c))
		ft_perror(token, scene, "Error: invalid plan\n");
	parse_plan_textures(scene, plane, token, c);
	add_obj(scene, plane, PL);
}
