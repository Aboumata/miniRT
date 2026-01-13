/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:44:42 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/10 23:59:05 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	is_normalized(t_vector3 vec)
{
	double	length;

	length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (length < 0.999 || length > 1.001)
		return (0);
	return (1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	get_next_line(-1);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	count_tokens(char **token)
{
	int	len;

	len = 0;
	while (token[len])
		len++;
	return (len);
}

void	cleanup_mlx(t_data *data)
{
	if (data->mlx.img != NULL)
	{
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
		data->mlx.img = NULL;
	}
	if (data->mlx.win != NULL)
	{
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		data->mlx.win = NULL;
	}
	if (data->mlx.mlx != NULL)
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		data->mlx.mlx = NULL;
	}
	exit(0);
}
