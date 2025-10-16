/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:08:02 by abdahman          #+#    #+#             */
/*   Updated: 2025/10/16 17:54:43 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void parse_line(t_scene *scene, char *line)
{
	char **token;

	token = ft_split(line, ' ');

	if (ft_strcmp("A", token[0]) == 0)
		parse_ambient(scene, token);
	else if (ft_strcmp("C", token[0]))
		parse_camera(scene, token);
	else if (ft_strcmp("sp", token[0]) == 0)
		parse_sphere(scene, token);
	else if (ft_strcmp("pl", token[0]))
		parse_plan(scene, token);
}
//A C L PL CY