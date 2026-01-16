/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_vectors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:49:54 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/16 10:00:00 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	skip_ws(char *s, int i)
{
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
			|| s[i] == '\r' || s[i] == '\v' || s[i] == '\f'))
		i++;
	return (i);
}

static int	bad_csv3(char *s)
{
	int	i;
	int	commas;

	if (!s)
		return (1);
	i = skip_ws(s, 0);
	commas = 0;
	if (!s[i] || s[i] == ',')
		return (1);
	while (s[i])
	{
		if (s[i] == ',')
		{
			if (++commas > 2)
				return (1);
			i = skip_ws(s, i + 1);
			if (!s[i] || s[i] == ',')
				return (1);
		}
		else
			i++;
	}
	return (commas != 2);
}

t_vector3	parse_vec(char **token, int indx, t_scene *scene)
{
	t_vector3	point;
	int			check;
	char		**position;

	if (bad_csv3(token[indx]))
		exit((write(2, "Error: invalid position\n", 24),
				ft_free_all(&scene->mem), free_split(token), 1));
	position = ft_split(token[indx], ',');
	if (count_tokens(position) != 3)
		exit((free_split(position), write(2, "Error: invalid position\n", 24),
				ft_free_all(&scene->mem), free_split(token), 1));
	check = 1;
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

	if (bad_csv3(token[indx]))
		ft_perror(token, scene, (write(2, "Error: invalid rgb\n", 19), NULL));
	rgb = ft_split(token[indx], ',');
	if (count_tokens(rgb) != 3)
		ft_perror(token, scene, (free_split(rgb),
				write(2, "Error: invalid rgb\n", 19), NULL));
	check = 1;
	color.r = ft_atoi_c(rgb[0], &check);
	color.g = ft_atoi_c(rgb[1], &check);
	color.b = ft_atoi_c(rgb[2], &check);
	free_split(rgb);
	if (!check)
		ft_perror(token, scene, "Error: invalid color\n");
	return (color);
}
