/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:32:56 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 21:43:05 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init_hit(t_hit *hit)
{
	hit->hit = 0;
	hit->t = INFINITY;
	hit->point.x = 0;
	hit->point.y = 0;
	hit->point.z = 0;
	hit->normal.x = 0;
	hit->normal.y = 0;
	hit->normal.z = 0;
	hit->color.r = 0;
	hit->color.g = 0;
	hit->color.b = 0;
	hit->object = NULL;
	hit->type = SP;
	hit->shininess = 0.0;
}

int	is_closer_hit(t_hit *current, double new_t)
{
	if (!current)
		return (0);
	if (new_t < EPSILON)
		return (0);
	if (new_t >= current->t)
		return (0);
	return (1);
}

void	update_hit(t_variables *var, t_vector3 normal,
		t_color color)
{
	var->hit->hit = 1;
	var->hit->t = var->t;
	var->hit->point = var->hit_point;
	var->hit->normal = normal;
	var->hit->color = color;
}
