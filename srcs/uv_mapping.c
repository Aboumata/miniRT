/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:00:00 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/14 16:00:00 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_uv	sphere_uv(t_vector3 point, t_vector3 center)
{
    t_uv		uv;
    t_vector3	p;
    double		theta;
    double		phi;

    p = vec_sub(point, center);
    p = vec_normalize(p);
    theta = atan2(p.z, p.x);
    phi = asin(p.y);
    uv.u = (theta + PI) / (2.0 * PI);
    uv.v = (phi + PI / 2.0) / PI;
    return (uv);
}

t_uv	plane_uv(t_vector3 point, t_vector3 plane_point)
{
    t_uv		uv;
    t_vector3	local;

    local = vec_sub(point, plane_point);
    uv.u = fmod(local.x, 1.0);
    uv.v = fmod(local.z, 1.0);
    if (uv.u < 0)
        uv.u += 1.0;
    if (uv.v < 0)
        uv.v += 1.0;
    return (uv);
}

t_uv	cylinder_uv(t_vector3 point, t_cylinders *cyl)
{
    t_uv		uv;
    t_vector3	local;
    t_vector3	proj;
    double		theta;
    double		height;

    local = vec_sub(point, cyl->center);
    height = vec_dot(local, cyl->dir);
    proj = vec_sub(local, vec_scale(cyl->dir, height));
    theta = atan2(proj.z, proj.x);
    uv.u = (theta + PI) / (2.0 * PI);
    uv.v = (height + cyl->height / 2.0) / cyl->height;
    if (uv.v < 0)
        uv.v = 0;
    if (uv.v > 1)
        uv.v = 1;
    return (uv);
}
