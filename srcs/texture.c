/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/15 19:35:18 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	copy_path(t_texture *tex, char *path, t_mem **mem)
{
	size_t	len;

	if (!tex || !path || !mem)
		return ;
	len = ft_strlen(path);
	tex->path = ft_malloc(len + 1, mem);
	ft_strlcpy(tex->path, path, len + 1);
}

t_texture	*load_texture(char *path, void *mlx, t_mem **mem)
{
	t_texture	*tex;

	if (!path || !mlx)
		return (NULL);
	tex = ft_malloc(sizeof(t_texture), mem);
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error: Failed to load texture: %s\n", path);
		return (NULL);
	}
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->data)
		return (NULL);
	copy_path(tex, path, mem);
	return (tex);
}

int	get_texture_color(t_texture *tex, int x, int y)
{
	int	*pixel;
	int	offset;

	if (!tex || !tex->data)
		return (0);
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	offset = y * (tex->line_len / 4) + x;
	pixel = (int *)tex->data;
	return (pixel[offset]);
}

double	get_bump_height(t_texture *bump, double u, double v)
{
	int		x;
	int		y;
	int		color;
	int		gray;

	if (!bump || !bump->data || bump->width <= 0 || bump->height <= 0)
		return (0.0);
	u = u - floor(u);
	if (u < 0.0)
		u += 1.0;
	v = v - floor(v);
	if (v < 0.0)
		v += 1.0;
	x = (int)(u * (double)(bump->width - 1));
	y = (int)(v * (double)(bump->height - 1));
	if (x < 0)
		x = 0;
	if (x >= bump->width)
		x = bump->width - 1;
	if (y < 0)
		y = 0;
	if (y >= bump->height)
		y = bump->height - 1;
	color = get_texture_color(bump, x, y);
	gray = ((color >> 16) & 0xFF) + ((color >> 8) & 0xFF) + (color & 0xFF);
	gray /= 3;
	return ((gray / 255.0 - 0.5) * 2.0);
}

t_color	sample_texture_color(t_texture *tex, t_uv uv)
{
	int		x;
	int		y;
	int		color_val;
	t_color	color;

	if (!tex || !tex->data)
		return ((t_color){255, 255, 255});
	uv.u = uv.u - floor(uv.u);
	if (uv.u < 0.0)
		uv.u += 1.0;
	uv.v = uv.v - floor(uv.v);
	if (uv.v < 0.0)
		uv.v += 1.0;
	x = (int)(uv.u * (double)(tex->width - 1));
	y = (int)(uv.v * (double)(tex->height - 1));
	color_val = get_texture_color(tex, x, y);
	color.r = (color_val >> 16) & 0xFF;
	color.g = (color_val >> 8) & 0xFF;
	color.b = color_val & 0xFF;
	return (color);
}
