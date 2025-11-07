/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 04:02:38 by aboumata          #+#    #+#             */
/*   Updated: 2025/11/07 04:02:40 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vector3	vec_add(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector3	vec_sub(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector3	vec_scale(t_vector3 v, double scale)
{
	t_vector3	result;

	result.x = v.x * scale;
	result.y = v.y * scale;
	result.z = v.z * scale;
	return (result);
}

double	vec_length(t_vector3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector3	vec_normalize(t_vector3 v)
{
	double		length;
	t_vector3	result;

	length = vec_length(v);
	if (length == 0)
		return (v);
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;
	return (result);
}

double	vec_dot(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector3	vec_cross(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

// void test_vectors(void)
// {
//     t_vector3 a;
//     t_vector3 b;
//     t_vector3 result;
//     double len;
//     double dot;
//
//     a.x = 1; a.y = 2; a.z = 3;
//     b.x = 4; b.y = 5; b.z = 6;
//
//     printf("\n=== Vector Math Tests ===\n\n");
//
//     printf("Test 1: Addition\n");
//     printf("A = (1, 2, 3)\n");
//     printf("B = (4, 5, 6)\n");
//     result = vec_add(a, b);
//     printf("A + B = (%f, %f, %f)\n", result.x, result.y, result.z);
//     printf("Expected: (5, 7, 9)\n\n");
//
//     printf("Test 2: Subtraction\n");
//     result = vec_sub(a, b);
//     printf("B - A = (%f, %f, %f)\n", result.x, result.y, result.z);
//     printf("Expected: (3, 3, 3)\n\n");
//
//     printf("Test 3: Scaling\n");
//     result = vec_scale(a, 2.0);
//     printf("A × 2 = (%f, %f, %f)\n", result.x, result.y, result.z);
//     printf("Expected: (2, 4, 6)\n\n");
//
//     printf("Test 4: Length\n");
//     len = vec_length(a);
//     printf("Length of A = %f\n", len);
//     printf("Expected: 3.741657... (sqrt(14))\n\n");
//
//     printf("Test 5: Normalize\n");
//     result = vec_normalize(a);
//     printf("Normalized A = (%f, %f, %f)\n", result.x, result.y, result.z);
//     len = vec_length(result);
//     printf("Length after normalize = %f\n", len);
//     printf("Expected length: 1.0\n\n");
//
//     printf("Test 6: Dot Product\n");
//     dot = vec_dot(a, b);
//     printf("A · B = %f\n", dot);
//     printf("Expected: 32 (1×4 + 2×5 + 3×6)\n\n");
//
//     printf("Test 7: Cross Product\n");
//     t_vector3 x = {1, 0, 0};
//     t_vector3 y = {0, 1, 0};
//     result = vec_cross(x, y);
//     printf("X × Y = (%f, %f, %f)\n", result.x, result.y, result.z);
//     printf("Expected: (0, 0, 1)\n\n");
//
//     printf("Test 8: Zero Vector Normalize\n");
//     t_vector3 zero = {0, 0, 0};
//     result = vec_normalize(zero);
//     printf("Normalized zero = (%f, %f, %f)\n", result.x, result.y, result.z);
//     printf("Expected: (0, 0, 0) - no crash!\n\n");
//
//     printf("=== All Tests Complete! ===\n\n");
// }
