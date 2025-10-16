/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:21:42 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/16 11:28:14 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

void init_scene(t_scene *scene)
{
    scene->camera = NULL;
    scene->ambient = NULL;
    scene->cylinders = NULL;
    scene->has_ambient = 0;
    scene->has_camera = 0;
    scene->has_light = 0;
    scene->planets = NULL;
    scene->spheres = NULL;
}

int main(int ac, char **av) {
    t_scene scene;

    if (ac != 2)
    {
        perror("There's are more than 2 arguments or less.");
        exit(1);
    }
    init_scene(&scene);
    parsing(&scene, av[1]);
}
