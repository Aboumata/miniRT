/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:58:04 by aboumata          #+#    #+#             */
/*   Updated: 2025/11/05 02:58:06 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	create_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	int	offset;
	int	*pixels;

	if ((x < 0 || x >= WIDTH) || (y < 0 || y >= HEIGHT))
		return ;
	pixels = (int *)data->mlx.addr;
	offset = y * (data->mlx.line_len / 4) + x;
	pixels[offset] = color;
}
