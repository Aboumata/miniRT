/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 00:16:12 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/22 00:16:26 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/miniRT.h"

void parse_triangle(t_scene *scene, char **token) {
    t_triangle *triangle;
    if (count_tokens(token) != 5)
        exit((perror("Error: invalid triangle"), 1));
    triangle = ft_malloc(sizeof(t_triangle), &(scene->mem));
    triangle->p1 = parse_vec(token[1]);
    triangle->p2 = parse_vec(token[2]);
    triangle->p3 = parse_vec(token[3]);
    triangle->color = parse_color(token[4]);
    add_obj(scene, triangle, TRIANGLE);
}
