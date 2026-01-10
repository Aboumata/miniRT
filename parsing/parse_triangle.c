/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 00:16:12 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/10 21:08:20 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_triangle(t_scene *scene, char **token)
{
	t_triangle	*triangle;

	if (count_tokens(token) != 5)
		ft_perror("Error: invalid triangle", token);
	triangle = ft_malloc(sizeof(t_triangle), &(scene->mem));
	triangle->p1 = parse_vec(token, 1);
	triangle->p2 = parse_vec(token, 2);
	triangle->p3 = parse_vec(token, 3);
	triangle->color = parse_color(token, 4);
	add_obj(scene, triangle, TRIANGLE);
}
