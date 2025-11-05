/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:58:14 by aboumata          #+#    #+#             */
/*   Updated: 2025/11/05 02:58:15 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	handle_key(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		cleanup_mlx(data);
		ft_free_all(&data->scene->mem);
		exit(0);
	}
	return (0);
}

int	handle_close(t_data *data)
{
	cleanup_mlx(data);
	ft_free_all(&data->scene->mem);
	exit(0);
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, 2, 1L << 0, handle_key, data);
	mlx_hook(data->mlx.win, 17, 0, handle_close, data);
}
