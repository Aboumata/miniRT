/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:56:24 by abdahman          #+#    #+#             */
/*   Updated: 2025/10/18 12:26:20 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

int	main(int ac, char **av)
{
	t_scene	scene;

	if (ac != 2)
	{
		perror("There's are more than 2 arguments or less.");
		exit(1);
	}
	ft_bzero(&scene, sizeof(t_scene));
	parsing(&scene, av[1]);
	write(1, "good\n", 5);
}
