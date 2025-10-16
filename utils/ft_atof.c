/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:50:19 by abdahman          #+#    #+#             */
/*   Updated: 2025/10/16 17:42:06 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double ft_atof(char *str)
{
	double (res), frac = 0, div = 10;
	int (i), sig = 1, dot_count = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
        if (str[i++] == '-')
		    sig = -1;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (dot_count == 0)
				res = res * 10 + (str[i] - '0');
			else
            {
				frac += (str[i] - '0') / div;
                div *= 10;
            }
		}
		else if (str[i] == '.' && dot_count < 1)
			dot_count++;              
		else
			exit((perror("invalid scene."), 1));
		i++;
	}
	return sig * (res + frac);
}