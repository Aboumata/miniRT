/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:12:39 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 09:58:34 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_cone(t_scene *scene, char **token)
{
	t_cone	*cone;

	if (count_tokens(token) != 6)
	{
		write(2, "Error: Invalid cone\n", 20);
		ft_perror(token, scene, NULL);
	}
	cone = ft_malloc(sizeof(t_cone), &(scene->mem));
	cone->center = parse_vec(token, 1, scene);
	cone->dir = parse_vec(token, 2, scene);
	if (!is_normalized(cone->dir))
		ft_perror(token, scene, "The cone is not normalized\n");
	cone->diameter = ft_atof(token[3], NULL);
	cone->height = ft_atof(token[4], NULL);
	if (cone->diameter < 0 || cone->height < 0)
	{
		write(2, "One of the diameter or height is not positive\n", 46);
		ft_perror(token, scene, NULL);
	}
	cone->color = parse_color(token, 5, scene);
	add_obj(scene, cone, CONE);
}
