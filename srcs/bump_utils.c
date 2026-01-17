/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 09:40:16 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/17 09:40:49 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double	wrap01(double x)
{
	x = x - floor(x);
	if (x < 0.0)
		x += 1.0;
	return (x);
}

double	clamp01(double x)
{
	if (x < 0.0)
		return (0.0);
	if (x > 1.0)
		return (1.0);
	return (x);
}

double	clamp(double x, double a, double b)
{
	if (x < a)
		return (a);
	if (x > b)
		return (b);
	return (x);
}
