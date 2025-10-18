/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_vectors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:49:54 by abdahman          #+#    #+#             */
/*   Updated: 2025/10/16 17:50:20 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vector3 parse_vec(char *token)
{
	t_vector3 point;
	char **position;

	position = ft_split(token, ',');
	if (count_tokens(position) != 3)
	{
		free_split(position);
		exit((perror("Error: invalid position\n"), 1));
	}

	point.x = ft_atof(position[0]);
	point.y = ft_atof(position[1]);
	point.z = ft_atof(position[2]);
	free_split(position);
	return (point);
}

int ft_atoi_c(char *str)
{
	int res = ft_atoi(str);
	if (res > 255 || res < 0)
		exit((perror("Error: You're out  range of RGB\n"), 1));
	return (res);
}

t_color parse_color(char *token)
{
	t_color color;
	char **rgb;

	rgb = ft_split(token, ',');
	if (count_tokens(rgb) != 3)
	{
		free_split(rgb);
		exit((perror("Error: invalid rgb\n"), 1));
	}
	color.r = ft_atoi_c(rgb[0]);
	color.g = ft_atoi_c(rgb[1]);
	color.b = ft_atoi_c(rgb[2]);
	free_split(rgb);
	return (color);
}
