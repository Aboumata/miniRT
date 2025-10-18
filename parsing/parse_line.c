/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:08:02 by abdahman          #+#    #+#             */
/*   Updated: 2025/10/18 16:53:04 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void parse_line(t_scene *scene, char *line)
{
	char **token;

	if (!line || line[0] == '\n' || line[0] == '\0')
		return;
	token = change_whitespace_and_split(line);
	if (!token || !token[0])
		return;
	if (ft_strcmp("A", token[0]) == 0)
		parse_ambient(scene, token);
	else if (ft_strcmp("C", token[0]) == 0)
		parse_camera(scene, token);
	else if (ft_strcmp("L", token[0]) == 0 || ft_strcmp("l", token[0]) == 0)
		parse_light(scene, token);
	else if (ft_strcmp("sp", token[0]) == 0)
		parse_sphere(scene, token);
	else if (ft_strcmp("pl", token[0]) == 0)
		parse_plan(scene, token);
	else if (ft_strcmp("cy", token[0]) == 0)
		parse_cylinder(scene, token);
	else
		exit((perror("Error: invalid object"), 1));
	free_split(token);
}
