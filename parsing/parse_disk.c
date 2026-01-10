/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_disk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:36:42 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/10 22:42:16 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	parse_disk(t_scene *scene, char **token)
{
	t_disk	*disk;

	if (count_tokens(token) != 5)
		ft_perror("Error: Invalid disk\n", token);
	disk = ft_malloc(sizeof(t_disk), &(scene->mem));
	disk->center = parse_vec(token, 1);
	disk->normal = parse_vec(token, 2);
	if (!is_normalized(disk->normal))
		ft_perror("Error: disk direction not normalized\n", token);
	disk->diameter = ft_atof(token[3], NULL);
	if (disk->diameter < 0)
		ft_perror("Error: the diameter is not positive\n", token);
	disk->color = parse_color(token, 4);
	add_obj(scene, disk, DISK);
}
