/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:54:21 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 10:01:57 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_light(t_scene *scene, char **token)
{
	t_light	**head;
	t_light	*light;

	head = &scene->light;
	if (count_tokens(token) != 4)
		ft_perror(token, scene, "Error: invalid light\n");
	light = ft_malloc(sizeof(t_light), &(scene->mem));
	light->pos = parse_vec(token, 1, scene);
	light->ratio = ft_atof(token[2], NULL);
	if (light->ratio < 0.0 || light->ratio > 1.0)
		ft_perror(token, scene, "Error: invalid ratio range\n");
	light->color = parse_color(token, 3, scene);
	light->next = *head;
	*head = light;
}
