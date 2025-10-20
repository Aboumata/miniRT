/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:54:21 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/18 18:44:33 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void parse_light (t_scene *scene, char **token)
{
    t_light **head;
    t_light *light;

    head = &scene->light;
    if (count_tokens(token) != 4)
        exit((perror("Error: invalid light\n"), 1));
    light = ft_malloc(sizeof(t_light), &(scene->mem));
    light->pos = parse_vec(token[1]);
    light->ratio = ft_atof(token[2]);
    if (light->ratio < 0.0 || light->ratio > 1.0)
        exit((perror("Error: invalid ratio range\n"), 1));
    light->color = parse_color(token[3]);
    light->next = *head;
    *head = light;
}
