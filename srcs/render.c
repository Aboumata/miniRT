/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:58:21 by aboumata          #+#    #+#             */
/*   Updated: 2025/11/05 02:58:22 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	test_render(t_data *data)
{
	int	x;
	int	y;
	int	r;
	int	g;
	int	b;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			r = (x * 255) / WIDTH;
			g = (y * 255) / HEIGHT;
			b = 128;
			put_pixel(data, x, y, create_color(r, g, b));
			x++;
		}
		y++;
	}
}

void	render(t_data *data)
{
	test_render(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
