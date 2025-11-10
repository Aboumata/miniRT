/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:32:47 by aboumata          #+#    #+#             */
/*   Updated: 2025/11/09 21:32:49 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static t_vector3	sphere_normal(t_vector3 hit_point, t_vector3 center)
{
	t_vector3	normal;

	normal = vec_sub(hit_point, center);
	normal = vec_normalize(normal);
	return (normal);
}

int	intersect_sphere(t_ray ray, t_spheres *sphere, t_hit *hit)
{
	t_vector3	oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		t;
	double		radius;
	t_vector3	hit_point;
	t_vector3	normal;

	oc = vec_sub(ray.origin, sphere->center);
	a = vec_dot(ray.direction, ray.direction);
	half_b = vec_dot(oc, ray.direction);
	radius = sphere->diameter / 2.0;
	c = vec_dot(oc, oc) - (radius * radius);
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	t = (-half_b - sqrt(discriminant)) / a;
	if (!is_closer_hit(hit, t))
		return (0);
	hit_point = ray_at(ray, t);
	normal = sphere_normal(hit_point, sphere->center);
	update_hit(hit, t, hit_point, normal, sphere->color);
	hit->object = sphere;
	hit->type = SP;
	return (1);
}

void	test_sphere_intersection(t_data *data) //just test the function if they are working
{
	t_ray		ray;
	t_hit		hit;
	t_object	*obj;
	t_spheres	*sp;

	printf("\n=== Testing Sphere Intersection ===\n\n");
	ray = create_ray(data, WIDTH / 2, HEIGHT / 2);
	printf("Testing center pixel ray:\n");
	printf("  Origin: (%.2f, %.2f, %.2f)\n", ray.origin.x, ray.origin.y,
		ray.origin.z);
	printf("  Direction: (%.2f, %.2f, %.2f)\n\n", ray.direction.x,
		ray.direction.y, ray.direction.z);
	obj = data->scene->object;
	while (obj)
	{
		if (obj->type == SP)
		{
			sp = (t_spheres *)obj->obj;
			printf("Testing sphere:\n");
			printf("  Center: (%.2f, %.2f, %.2f)\n", sp->center.x, sp->center.y,
				sp->center.z);
			printf("  Radius: %.2f\n", sp->diameter / 2.0);
			init_hit(&hit);
			if (intersect_sphere(ray, sp, &hit))
			{
				printf("  ✓ HIT! Distance: %.2f\n", hit.t);
				printf("  Hit point: (%.2f, %.2f, %.2f)\n", hit.point.x,
					hit.point.y, hit.point.z);
				printf("  Normal: (%.2f, %.2f, %.2f)\n\n", hit.normal.x,
					hit.normal.y, hit.normal.z);
			}
			else
				printf("  ✗ MISS\n\n");
		}
		obj = obj->next;
	}
}
