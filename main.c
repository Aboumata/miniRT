/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:21:42 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/15 19:21:45 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int main(int ac, char **av) {
    t_scene scene;
    if (ac != 2)
    {
        perror("There's are more than 2 arguments or less.");
        exit(1);
    }
    parsing(&scene, av[1]);
}
