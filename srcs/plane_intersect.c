/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:33:36 by aboumata          #+#    #+#             */
/*   Updated: 2025/11/09 21:33:37 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"


/*
 * Ray: p(t) = origin + t * direction
 * Plane: (P - plane_point) * normal = 0
 *
 * SOLVE!
 *
 * (origin + t * direction - plane_point) * normal = 0;
 * normal * origin + t * (direction * normal) - plane_point * normal = 0
 * t * (direction * normal) = plane_point * normal - normal * origin
 * t * (direction * normal) = normal * (plane_point - origin)
 * t = normal * (plane_point - origin) / (direction * normal)
 *
 */

static t_vector3 plane_normal(t_planes *plane, t_ray ray)
{
    t_vector3 normal;

    normal = plane->normal;
    if (vec_dot(ray.direction , plane->normal) > 0)
        normal = vec_scale(plane->normal, -1);
    return (normal);
}

int intersect_plane(t_ray ray, t_planes *plane, t_hit *hit)
{
    double      denom;
    double      numer;
    double      t;
    t_vector3   to_plane;
    t_vector3   hit_point;
    t_vector3   normal;

    denom = vec_dot(ray.direction, plane->normal);
    if (fabs(denom) < EPSILON)
        return (0);
    to_plane = vec_sub(plane->point, ray.origin);
    numer = vec_dot(to_plane, plane->normal);
    t = numer / denom;
    if (!is_closer_hit(hit, t))
        return (0);
    hit_point = vec_add(ray.origin, vec_scale(ray.direction, t));
    normal = plane_normal(plane, ray);
    update_hit(hit, t, hit_point, normal, plane->color);
    hit->object = plane;
    hit->type = PL;
    return (1);
}
