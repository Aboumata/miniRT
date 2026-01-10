/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:08:02 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/10 21:01:08 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	dispatch_parser(t_scene *scene, char **token, char *key)
{
	if (ft_strcmp("A", key) == 0)
		parse_ambient(scene, token);
	else if (ft_strcmp("C", key) == 0)
		parse_camera(scene, token);
	else if (ft_strcmp("L", key) == 0 || ft_strcmp("l", key) == 0)
		parse_light(scene, token);
	else if (ft_strcmp("sp", key) == 0)
		parse_sphere(scene, token);
	else if (ft_strcmp("pl", key) == 0)
		parse_plan(scene, token);
	else if (ft_strcmp("cy", key) == 0)
		parse_cylinder(scene, token);
	else if (ft_strcmp("co", key) == 0)
		parse_cone(scene, token);
	else if (ft_strcmp("tr", key) == 0)
		parse_triangle(scene, token);
	else if (ft_strcmp("di", key) == 0)
		parse_disk(scene, token);
	else
		ft_perror("Error: invalid object", token);
}

void	parse_line(t_scene *scene, char *line)
{
	char	**token;

	if (!line || line[0] == '\n' || line[0] == '\0' || line[0] == '#')
		return ;
	token = change_whitespace_and_split(line);
	if (!token || !token[0])
		return ;
	dispatch_parser(scene, token, token[0]);
	free_split(token);
}
