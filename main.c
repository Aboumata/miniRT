/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:56:24 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/11 09:20:08 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

int	main(int ac, char **av)
{
	t_scene	scene;
	t_data	data;

	if (ac != 2)
	{
		write(2, "There are two arguments or more/fewer.", 38);
		exit(1);
	}
	ft_bzero(&scene, sizeof(t_scene));
	parsing(&scene, av[1]);
	data.scene = &scene;
	setup_camera(&data);
	if (initialize_mlx(&data) == -1)
	{
		ft_free_all(&scene.mem);
		return (1);
	}
	render(&data);
	setup_hooks(&data);
	mlx_loop(data.mlx.mlx);
	cleanup_mlx(&data);
	ft_free_all(&scene.mem);
	return (0);
}
