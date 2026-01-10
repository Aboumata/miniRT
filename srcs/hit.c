/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:32:56 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/09 18:20:52 by abdahman         ###   ########.fr       */
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
	if (new_t < EPSILON)
		return (0);
	if (new_t >= current->t)
		return (0);
	return (1);
}

void	update_hit(t_hit *hit, double t, t_vector3 point, t_vector3 normal,
		t_color color)
{
	hit->hit = 1;
	hit->t = t;
	hit->point = point;
	hit->normal = normal;
	hit->color = color;
}
