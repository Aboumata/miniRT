/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:45:34 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/11 09:59:56 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	ft_free_all(t_mem **mem)
{
	t_mem	*tmp;
	t_mem	*node;

	if (!mem || !*mem)
		return ;
	tmp = *mem;
	get_next_line(-1);
	while (tmp)
	{
		node = tmp;
		tmp = tmp->next;
		free(node->ptr);
		free(node);
	}
	*mem = NULL;
}

static t_texture	*get_obj_bump_map(t_object *obj)
{
	if (!obj || !obj->obj)
		return (NULL);
	if (obj->type == SP)
		return (((t_spheres *)obj->obj)->bump_map);
	if (obj->type == PL)
		return (((t_planes *)obj->obj)->bump_map);
	if (obj->type == CY)
		return (((t_cylinders *)obj->obj)->bump_map);
	return (NULL);
}

void	destroy_scene_textures(t_scene *scene, void *mlx)
{
	t_object	*obj;
	t_texture	*tex;

	if (!scene || !mlx)
		return ;
	obj = scene->object;
	while (obj)
	{
		tex = get_obj_bump_map(obj);
		if (tex)
			destroy_texture(mlx, tex);
		obj = obj->next;
	}
}

void	cleanup_all(t_data *data)
{
	if (!data)
		return ;
	if (data->scene)
		destroy_scene_textures(data->scene, data->mlx.mlx);
	if (data->scene)
	{
		ft_free_all(&data->scene->mem);
		data->scene = NULL;
	}
	cleanup_mlx(data);
}


void	*ft_malloc(size_t size, t_mem **mem)
{
	void	*ptr;
	t_mem	*node;

	ptr = malloc(size);
	if (!ptr)
		exit((perror("malloc filed."), 1));
	node = malloc(sizeof(t_mem));
	if (!node)
		exit((perror("malloc filed."), 1));
	node->ptr = ptr;
	node->next = *mem;
	*mem = node;
	return (ptr);
}
