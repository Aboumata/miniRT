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
		exit((perror("invalid scene\n"), 1));
	point.x = ft_atof(position[0]);
	point.y = ft_atof(position[1]);
	point.z = ft_atof(position[2]);
	return (point);
}

int ft_atoi_c(char *str)
{
	long res = ft_atoi(str);
	if (res > 255)
		res = 255;
	else if (res < 0)
		res = 0;
	return (res);
}

t_color parse_color(char *token)
{
	t_color color;
	char **rgb;

	rgb = ft_split(token, ',');
	if (count_tokens(rgb) != 3)
		exit((perror("invalid scene\n"), 1));
	color.r = ft_atoi_c(rgb[0]);
	color.g = ft_atoi_c(rgb[1]);
	color.b = ft_atoi_c(rgb[2]);
	return (color);
}
