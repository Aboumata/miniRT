/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:57:01 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/09 10:07:13 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	ft_continue(t_planes *pl, char **token, int c)
{
	if (c == 6)
	{
		pl->shininess = ft_atof(token[4]);
		if (pl->shininess < 0.0)
			exit((perror("the shininess should always be positive"), 0)); // khat ndiro free 9bl exit ...
		if (ft_strcmp(token[5], "cb"))
			exit((perror("invalid flag"), 0)); // khat ndiro free 9bl exit ...
		pl->Checkerboard = 1;
	}
	if (c == 5)
	{
		if (!ft_strcmp(token[4], "cb"))
		{
			pl->Checkerboard = 1;
			return ;
		}
		pl->shininess = ft_atof(token[4]);
		if (pl->shininess < 0.0)
			exit((perror("the shininess should always be positive"), 0)); // khat ndiro free 9bl exit ...
	}
	pl->Checkerboard = 0;
}

void	parse_plan(t_scene *scene, char **token)
{
	t_planes	*plane;
	int			c;

	c = count_tokens(token);
	if (c != 4 && c != 5 && c != 6)
	{
		write(2, "Error: invalid plan\n", 20);
		exit(1); // khat ndiro free 9bl exit ...
	}
	plane = ft_malloc(sizeof(t_planes), &(scene->mem));
	plane->point = parse_vec(token[1]);
	plane->color = parse_color(token[3]);
	plane->normal = parse_vec(token[2]);
	if (!is_normalized(plane->normal))
	{
		write(2, "Error: plan not normalized\n", 27);
		exit(1); // khat ndiro free 9bl exit ...
	}
	ft_continue(plane, token, c);
	add_obj(scene, plane, PL);
}
