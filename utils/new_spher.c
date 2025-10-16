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

void add_obj(t_scene *scene, void *ptr, t_obj_types type)
{
	t_object **head = &(scene->object);
	t_object *node = ft_malloc(sizeof(t_object), &(scene->mem));
	node->obj = ptr;
	node->type = type;
	node->next = *head;
	*head = node;
	if (node->type == SP)
	{
		t_spheres *sphere = (t_spheres *)ptr;
		printf("add object:\n");
		printf("Sphere:\n");
		printf("  Center: x=%.2f, y=%.2f, z=%.2f\n", 
			sphere->center.x, sphere->center.y, sphere->center.z);
		printf("  Diameter: %.2f\n", sphere->diameter);
		printf("  Color: R=%d, G=%d, B=%d\n", 
			sphere->color.r, sphere->color.g, sphere->color.b);
	}
	return ;
}
