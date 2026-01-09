/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:50:19 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/09 10:02:49 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	handle_sign(const char *str, int *i)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
		{
			(*i)++;
			return (-1);
		}
		(*i)++;
	}
	return (1);
}

static void	process_digit(char c, t_atof *data)
{
	if (data->dot_count == 0)
		data->res = data->res * 10 + (c - '0');
	else
	{
		data->frac += (c - '0') / data->div;
		data->div *= 10;
	}
}

double	ft_atof(char *str)
{
	t_atof	data;
	int		i;
	int		sig;

	data.res = 0;
	data.frac = 0;
	data.div = 10;
	data.dot_count = 0;
	i = 0;
	sig = handle_sign(str, &i);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			process_digit(str[i], &data);
		else if (str[i] == '.' && data.dot_count < 1)
			data.dot_count++;
		else
			exit((perror("Error: invalid number"), 1)); 
		i++;
	}
	return (sig * (data.res + data.frac));
}
