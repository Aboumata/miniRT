/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:30:28 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/16 21:30:29 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/miniRT.h"

void parse_ambient(t_scene *scene, char **token)
{
    if (count_tokens(token) != 3 || scene->has_ambient > 0)
        exit((perror("invalid scene\n"), 1));
    scene->has_ambient++;
    scene->ambient.ratio = ft_atof(token[1]);
    if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
         exit((perror("invalid scene\n"), 1));
    scene->ambient.color = parse_color(token[2]);
}
