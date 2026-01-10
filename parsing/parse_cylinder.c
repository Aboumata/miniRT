/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:41:29 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/10 22:46:04 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	ft_perror(char *mess, char **token)
{
	free_split(token);
	perror(mess);
	exit(1);
}

void	parse_cylinder(t_scene *scene, char **token)
{
	t_cylinders	*cylinder;

	if (count_tokens(token) != 6 && count_tokens(token) != 7)
		exit((free_split(token), perror("invalid cylinder\n"), 1));
	cylinder = ft_malloc(sizeof(t_cylinders), &(scene->mem));
	cylinder->center = parse_vec(token, 1);
	cylinder->diameter = ft_atof(token[3], NULL);
	cylinder->height = ft_atof(token[4], NULL);
	if (cylinder->diameter < 0 || cylinder->height < 0)
		ft_perror("One of the diameter or height is not positive\n", token);
	cylinder->color = parse_color(token, 5);
	cylinder->dir = parse_vec(token, 2);
	if (!is_normalized(cylinder->dir))
		ft_perror("Error: cylinder direction not normalized\n", token);
	if (count_tokens(token) == 7)
	{
		cylinder->shininess = ft_atof(token[6], NULL);
		if (cylinder->shininess < 0)
			ft_perror("Error: invalid shininess", token);
	}
	else
		cylinder->shininess = 0.0;
	add_obj(scene, cylinder, CY);
}
