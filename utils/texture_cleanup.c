/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/15 18:13:29 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
** These functions are used by your cleanup to destroy MLX XPM images.
** IMPORTANT: mlx_destroy_image() must be called BEFORE mlx_destroy_display().
*/

void	destroy_texture(void *mlx, t_texture *tex)
{
	if (!mlx || !tex)
		return ;
	if (tex->img)
	{
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
	}
	tex->data = NULL;
}

void	destroy_scene_textures(t_scene *scene, void *mlx)
{
	t_object	*obj;

	if (!scene || !mlx)
		return ;
	obj = scene->object;
	while (obj)
	{
		if (obj->type == SP)
		{
			destroy_texture(mlx, ((t_spheres *)obj->obj)->bump_map);
			destroy_texture(mlx, ((t_spheres *)obj->obj)->albedo_map);
		}
		else if (obj->type == PL)
		{
			destroy_texture(mlx, ((t_planes *)obj->obj)->bump_map);
			destroy_texture(mlx, ((t_planes *)obj->obj)->albedo_map);
		}
		else if (obj->type == CY)
		{
			destroy_texture(mlx, ((t_cylinders *)obj->obj)->bump_map);
			destroy_texture(mlx, ((t_cylinders *)obj->obj)->albedo_map);
		}
		obj = obj->next;
	}
}

void	cleanup_mlx(t_data *data)
{
	if (!data || !data->mlx.mlx)
		return ;
	destroy_scene_textures(data->scene, data->mlx.mlx);
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
}
