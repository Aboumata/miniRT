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

# include "../includes/miniRT.h"

int create_color (int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

void put_pixel(t_data *data, int x, int y, int color)
{
    int byte_offset;

    if ((x < 0 || x >= WIDTH) && (y < 0 || y >= HEIGHT))
    {
            write(1, "Don't draw, out of bounds", 25);
            return;
    }
    byte_offset = y * data->mlx.line_len + x * (data->mlx.bpp / 8);
    ((int *)data->mlx.addr)[byte_offset / 4] = color;

}
