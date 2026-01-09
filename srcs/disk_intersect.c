/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 10:32:37 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/09 10:42:36 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int intersect_disk(t_ray ray, t_disk *disk, t_hit *hit)
{
    t_vector3 normal;
    t_vector3 to_disk;
    t_vector3 hit_point;
    t_vector3 p_to_center;
    double denom;
    double numer;
    double t;
    double r;

    normal = disk->normal;
    denom = vec_dot(ray.direction, normal);

    if (fabs(denom) < EPSILON)
        return (0);

    if (denom > 0)
    {
        normal = vec_scale(normal, -1);
        denom = -denom;
    }

    to_disk = vec_sub(disk->center, ray.origin);
    numer = vec_dot(to_disk, normal);
    t = numer / denom;

    if (t < EPSILON || t > hit->t)
        return (0);

    hit_point = ray_at(ray, t);
    p_to_center = vec_sub(hit_point, disk->center);

    r = disk->diameter / 2;
    if (vec_dot(p_to_center, p_to_center) > r * r)
        return (0);

    update_hit(hit, t, hit_point, normal, disk->color);
    hit->object = disk;
    hit->type = DISK;
    return (1);
}
