/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:41:29 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/12 16:00:49 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	ft_perror(char **token, t_scene *scene, char *mes)
{
	if (token)
		free_split(token);
	if (scene && scene->mem)
		ft_free_all(&scene->mem);
	get_next_line(-1);
	printf("%s", mes);
	exit(0);
}

void	parse_cylinder(t_scene *scene, char **token)
{
	t_cylinders	*cylinder;

	if (count_tokens(token) != 6 && count_tokens(token) != 7)
		ft_perror(token, scene, "invalid cylinder\n");
	cylinder = ft_malloc(sizeof(t_cylinders), &(scene->mem));
	cylinder->center = parse_vec(token, 1, scene);
	cylinder->diameter = ft_atof(token[3], NULL);
	cylinder->height = ft_atof(token[4], NULL);
	if (cylinder->diameter < 0 || cylinder->height < 0)
		ft_perror(token, scene,
			"One of the diameter or height is not positive\n");
	cylinder->color = parse_color(token, 5, scene);
	cylinder->dir = parse_vec(token, 2, scene);
	if (!is_normalized(cylinder->dir))
		ft_perror(token, scene, "Error: cylinder direction not normalized\n");
	if (count_tokens(token) == 7)
	{
		cylinder->shininess = ft_atof(token[6], NULL);
		if (cylinder->shininess < 0)
			ft_perror(token, scene, "Error: invalid shininess");
	}
	else
		cylinder->shininess = 0.0;
	add_obj(scene, cylinder, CY);
}
