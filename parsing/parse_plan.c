/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:57:01 by abdahman          #+#    #+#             */
/*   Updated: 2025/10/16 18:01:51 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_plan(t_scene *scene, char **token)
{
	t_planes	*plan;

	if (count_tokens(token) != 4)
		exit((perror("Error: invalid plan\n"), 1));
	plan = ft_malloc(sizeof(t_planes), &(scene->mem));
	plan->point = parse_vec(token[1]);
	plan->color = parse_color(token[3]);
	plan->normal = parse_vec(token[2]);
	if (!is_normalized(plan->normal))
		exit((perror("Error: plan not normalized\n"), 1));
	add_obj(scene, plan, PL);
}
