/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 08:43:03 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/11 10:48:19 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
	(P - C) · V = ||P - C|| cos(θ) <- cone
	--- P = O + D.t 			   <- cho3a3
	ba3d ta3wid wa al hisab .. :
	a = 
*/

// int	intersect_cone(t_ray ray, t_cone *cone, t_hit *hit)
// {
// 	t_vector3	cone_head;
// 	t_vector3	oc;

// 	double (a), r = cone->diameter / 2.0, half_b, c, delta, t, bita,
// 	tan2 = (r * r) / (cone->height * cone->height);
// 	oc = vec_sub(ray.origin, cone->center);
//     return (1);
// }