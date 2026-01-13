/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/13 00:00:00 by abdahman         ###   ########.fr       */
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

void	destroy_scene_bump_maps(t_scene *scene, void *mlx)
{
	t_object	*obj;

	if (!scene || !mlx)
		return ;
	obj = scene->object;
	while (obj)
	{
		if (obj->type == SP)
			destroy_texture(mlx, ((t_spheres *)obj->obj)->bump_map);
		else if (obj->type == PL)
			destroy_texture(mlx, ((t_planes *)obj->obj)->bump_map);
		else if (obj->type == CY)
			destroy_texture(mlx, ((t_cylinders *)obj->obj)->bump_map);
		obj = obj->next;
	}
}
