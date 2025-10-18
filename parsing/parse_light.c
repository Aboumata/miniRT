/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:54:21 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/17 09:54:22 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void parse_light (t_scene *scene, char **token) {
    if (count_tokens(token) != 4 || scene->has_light > 0)
        exit((perror("Error: invalid light\n"), 1));
    scene->has_light++;
    scene->light.pos = parse_vec(token[1]);
    scene->light.ratio = ft_atof(token[2]);
    if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
        exit((perror("Error: invalid ratio range\n"), 1));
    scene->light.color = parse_color(token[3]);
}
