/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:32:47 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 14:55:14 by abdahman         ###   ########.fr       */
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

double	help(double t, double sqrt_d, double half_b, double a)
{
	t = (-half_b - sqrt_d) / a;
	if (t < EPSILON)
		t = (-half_b + sqrt_d) / a;
	return (t);
}

int	intersect_sphere(t_ray ray, t_spheres *sphere, t_hit *hit)
{
	t_variables	var;
	t_vector3	normal;

	double (a), sqrt_d, radius, t = 0.0, half_b, c, discriminant;
	var.hit = hit;
	var.oc = vec_sub(ray.origin, sphere->center);
	a = vec_dot(ray.direction, ray.direction);
	half_b = vec_dot(var.oc, ray.direction);
	radius = sphere->diameter / 2.0;
	c = vec_dot(var.oc, var.oc) - (radius * radius);
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	sqrt_d = sqrt(discriminant);
	t = help(t, sqrt_d, half_b, a);
	if (t < EPSILON || t > hit->t)
		return (0);
	var.hit_point = ray_at(ray, t);
	var.t = t;
	normal = sphere_normal(var.hit_point, sphere->center);
	update_hit(&var, normal, sphere->color);
	hit->object = sphere;
	hit->type = SP;
	hit->shininess = sphere->shininess;
	return (1);
}

//printf("Sphere shininess stored: %f\n", sphere->shininess);
// void	test_sphere_intersection(t_data *data)
// just test the function if they are working
// {
// 	t_ray		ray;
// 	t_hit		hit;
// 	t_object	*obj;
// 	t_spheres	*sp;
//
// 	printf("\n=== Testing Sphere Intersection ===\n\n");
// 	ray = create_ray(data, WIDTH / 2, HEIGHT / 2);
// 	printf("Testing center pixel ray:\n");
// 	printf("  Origin: (%.2f, %.2f, %.2f)\n", ray.origin.x, ray.origin.y,
// 		ray.origin.z);
// 	printf("  Direction: (%.2f, %.2f, %.2f)\n\n", ray.direction.x,
// 		ray.direction.y, ray.direction.z);
// 	obj = data->scene->object;
// 	while (obj)
// 	{
// 		if (obj->type == SP)
// 		{
// 			sp = (t_spheres *)obj->obj;
// 			printf("Testing sphere:\n");
// 			printf("  Center: (%.2f, %.2f, %.2f)\n", sp->center.x, sp->center.y,
// 				sp->center.z);
// 			printf("  Radius: %.2f\n", sp->diameter / 2.0);
// 			init_hit(&hit);
// 			if (intersect_sphere(ray, sp, &hit))
// 			{
// 				printf("  ✓ HIT! Distance: %.2f\n", hit.t);
// 				printf("  Hit point: (%.2f, %.2f, %.2f)\n", hit.point.x,
// 					hit.point.y, hit.point.z);
// 				printf("  Normal: (%.2f, %.2f, %.2f)\n\n", hit.normal.x,
// 					hit.normal.y, hit.normal.z);
// 			}
// 			else
// 				printf("  ✗ MISS\n\n");
// 		}
// 		obj = obj->next;
// 	}
// }