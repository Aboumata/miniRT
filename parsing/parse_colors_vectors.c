/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_vectors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:49:54 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/11 09:54:57 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vector3	parse_vec(char **token, int indx, t_scene *scene)
{
	t_vector3	point;
	int			check;
	char		**position;

	position = ft_split(token[indx], ',');
	check = 1;
	if (count_tokens(position) != 3)
	{
		free_split(position);
		write(2, "Error: invalid position\n", 24);
		exit((ft_free_all(&scene->mem), free_split(token), 1));
	}
	point.x = ft_atof(position[0], &check);
	point.y = ft_atof(position[1], &check);
	point.z = ft_atof(position[2], &check);
	free_split(position);
	if (!check)
		ft_perror(token, scene, "invalid vector\n");
	return (point);
}

int	ft_atoi_c(char *str, int *check)
{
	int	res;

	res = (int)ft_atof(str, check);
	if (res > 255 || res < 0)
	{
		write(2, "Error: You're out range of RGB\n", 32);
		*check = 1;
	}
	return (res);
}

t_color	parse_color(char **token, int indx, t_scene *scene)
{
	t_color	color;
	int		check;
	char	**rgb;

	rgb = ft_split(token[indx], ',');
	check = 1;
	if (count_tokens(rgb) != 3)
	{
		free_split(rgb);
		write(2, "Error: invalid rgb\n", 19);
		ft_perror(token, scene, NULL);
	}
	color.r = ft_atoi_c(rgb[0], &check);
	color.g = ft_atoi_c(rgb[1], &check);
	color.b = ft_atoi_c(rgb[2], &check);
	free_split(rgb);
	if (!check)
		ft_perror(token, scene, "Error: invalid color\n");
	return (color);
}
