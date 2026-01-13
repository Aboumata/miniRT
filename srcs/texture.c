/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:00:00 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static double	wrap01(double u)
{
	u = u - floor(u);
	if (u < 0.0)
		u += 1.0;
	return (u);
}

static double	clamp01(double v)
{
	if (v < 0.0)
		return (0.0);
	if (v > 1.0)
		return (1.0);
	return (v);
}

t_texture	*load_texture(char *path, void *mlx, t_mem **mem)
{
	t_texture	*texture;
	size_t		len;

	if (!path || !mlx)
		return (NULL);
	texture = ft_malloc(sizeof(t_texture), mem);
	ft_bzero(texture, sizeof(t_texture));
	texture->img = mlx_xpm_file_to_image(mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (NULL);
	texture->data = mlx_get_data_addr(texture->img,
			&texture->bpp, &texture->line_len, &texture->endian);
	if (!texture->data)
		return (NULL);
	len = ft_strlen(path);
	texture->path = ft_malloc(len + 1, mem);
	ft_strlcpy(texture->path, path, len + 1);
	return (texture);
}

void	destroy_texture(void *mlx, t_texture *tex)
{
	if (!mlx || !tex || !tex->img)
		return ;
	mlx_destroy_image(mlx, tex->img);
	tex->img = NULL;
	tex->data = NULL;
}

int	get_texture_color(t_texture *tex, int x, int y)
{
	unsigned char	*p;
	int				bytes;

	if (!tex || !tex->data || tex->bpp <= 0)
		return (0);
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	bytes = tex->bpp / 8;
	p = (unsigned char *)(tex->data + (y * tex->line_len) + (x * bytes));
	if (bytes == 4)
		return (*(unsigned int *)p);
	if (bytes == 3)
		return ((p[2] << 16) | (p[1] << 8) | p[0]);
	return (0);
}

double	get_bump_height(t_texture *bump, double u, double v)
{
	int		x;
	int		y;
	int		color;
	int		r;

	if (!bump || !bump->data || bump->width <= 0 || bump->height <= 0)
		return (0.0);
	u = wrap01(u);
	v = clamp01(v);
	x = (int)(u * (double)bump->width);
	y = (int)(v * (double)bump->height);
	if (x >= bump->width)
		x = bump->width - 1;
	if (y >= bump->height)
		y = bump->height - 1;
	color = get_texture_color(bump, x, y);
	r = (color >> 16) & 0xFF;
	return ((r / 255.0 - 0.5) * 2.0);
}
