/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:41:29 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/17 22:41:30 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_cylinder(t_scene *scene, char **token)
{
	t_cylinders	*cylinder;

	if (count_tokens(token) != 6 && count_tokens(token) != 7)
		exit((perror("invalid cylinder\n"), 1));
	cylinder = ft_malloc(sizeof(t_cylinders), &(scene->mem));
	cylinder->center = parse_vec(token[1]);
	cylinder->diameter = ft_atof(token[3]);
	cylinder->height = ft_atof(token[4]);
	if (cylinder->diameter < 0 || cylinder->height < 0)
		exit((perror(("One of the diameter or height is not positive\n")), 1));
	cylinder->color = parse_color(token[5]);
	cylinder->dir = parse_vec(token[2]);
	if (!is_normalized(cylinder->dir))
		exit((perror("Error: cylinder direction not normalized\n"), 1));
	if (count_tokens(token) == 7)
	{
		cylinder->shininess = ft_atof(token[6]);
		if (cylinder->shininess < 0)
			exit((perror("Error: shininess should be non-negative\n"), 1));
	}
	else
		cylinder->shininess = 0.0;
	add_obj(scene, cylinder, CY);
}
