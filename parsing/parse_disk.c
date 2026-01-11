/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_disk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:36:42 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 11:06:21 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_disk(t_scene *scene, char **token)
{
	t_disk	*disk;

	if (count_tokens(token) != 5)
		ft_perror(token, scene, "Error: Invalid disk\n");
	disk = ft_malloc(sizeof(t_disk), &(scene->mem));
	disk->center = parse_vec(token, 1, scene);
	disk->normal = parse_vec(token, 2, scene);
	if (!is_normalized(disk->normal))
		ft_perror(token, scene, "Error: disk direction not normalized\n");
	disk->diameter = ft_atof(token[3], NULL);
	if (disk->diameter < 0)
		ft_perror(token, scene, "Error: the diameter is not positive\n");
	disk->color = parse_color(token, 4, scene);
	printf("%d .. %d .. %d\n", disk->color.b, disk->color.g, disk->color.r);
	add_obj(scene, disk, DISK);
}
