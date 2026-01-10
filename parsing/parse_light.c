/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:54:21 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/10 22:41:46 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_light(t_scene *scene, char **token)
{
	t_light	**head;
	t_light	*light;

	head = &scene->light;
	if (count_tokens(token) != 4)
		ft_perror("Error: invalid light\n", token);
	light = ft_malloc(sizeof(t_light), &(scene->mem));
	light->pos = parse_vec(token, 1);
	light->ratio = ft_atof(token[2], NULL);
	if (light->ratio < 0.0 || light->ratio > 1.0)
		ft_perror("Error: invalid ratio range\n", token);
	light->color = parse_color(token, 3);
	light->next = *head;
	*head = light;
}
