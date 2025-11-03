/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:04:44 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/31 16:04:46 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
	{
		write(2, "Error: MLX init failed\n", 24);
		cleanup_mlx(data);
		return (-1);
	}
	return (0);
}

static int	create_window(t_data *data)
{
	data->mlx.win = mlx_new_window(data->mlx.mlx, WIDTH, HEIGHT, "miniRT");
	if (data->mlx.win == NULL)
	{
		write(2, "Error: Window creation failed\n", 30);
		cleanup_mlx(data);
		return (-1);
	}
	return (0);
}

static int	create_image(t_data *data)
{
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	if (data->mlx.img == NULL)
	{
		write(2, "Error: Image creation failed\n", 29);
		cleanup_mlx(data);
		return (-1);
	}
	return (0);
}

static int	get_address(t_data *data)
{
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.line_len, &data->mlx.endian);
	if (data->mlx.addr == NULL)
	{
		write(2, "Error: Get address failed\n", 26);
		cleanup_mlx(data);
		return (-1);
	}
	return (0);
}

int	initialize_mlx(t_data *data)
{
	if (init_mlx(data) == -1)
		return (-1);
	if (create_image(data) == -1)
		return (-1);
	if (create_window(data) == -1)
		return (-1);
	if (get_address(data) == -1)
		return (-1);
	return (0);
}
