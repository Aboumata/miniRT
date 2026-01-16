/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:58:14 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/15 19:12:35 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	handle_key(int keycode, t_data *data)
{
	if (keycode == 65307 || keycode == 53)
		mlx_loop_end(data->mlx.mlx);
	return (0);
}

int	handle_close(t_data *data)
{
	mlx_loop_end(data->mlx.mlx);
	return (0);
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, 2, 1L << 0, handle_key, data);
	mlx_hook(data->mlx.win, 17, 0, handle_close, data);
}
