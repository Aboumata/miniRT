/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_spher.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:50:04 by abdahman          #+#    #+#             */
/*   Updated: 2025/10/16 17:49:36 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	add_obj(t_scene *scene, void *ptr, t_obj_types type)
{
	t_object	**head;
	t_object	*node;

	head = &(scene->object);
	node = ft_malloc(sizeof(t_object), &(scene->mem));
	node->obj = ptr;
	node->type = type;
	node->next = *head;
	*head = node;
}
