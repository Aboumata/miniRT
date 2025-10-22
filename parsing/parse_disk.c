/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_disk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:36:42 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/22 08:36:44 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/miniRT.h"

void parse_disk(t_scene *scene, char **token) {
    t_disk *disk;

    if (count_tokens(token) != 5)
        exit((perror("Error: Invalid disk\n"), 1));
    disk = ft_malloc(sizeof(t_disk), &(scene->mem));
    disk->center = parse_vec(token[1]);
    disk->normal = parse_vec(token[2]);
    if (!is_normalized(disk->normal))
        exit((perror("Error: disk direction not normalized\n"), 1));
    disk->diameter = ft_atof(token[3]);
    if (disk->diameter < 0)
        exit((perror(("Error: the diameter is not positive\n")), 1));
    disk->color = parse_color(token[4]);
    add_obj(scene, disk, DISK);
}
