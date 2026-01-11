/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:30:28 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 11:25:29 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_ambient(t_scene *scene, char **token)
{
	if (count_tokens(token) != 3 || scene->has_ambient > 0)
		ft_perror(token, scene, "Error: invalid ambient\n");
	scene->has_ambient++;
	scene->ambient.ratio = ft_atof(token[1], NULL);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		ft_perror(token, scene, "Error : Invalid ambient ratio\n");
	scene->ambient.color = parse_color(token, 2, scene);
}
