/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:27:15 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/11 12:38:54 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

char	**change_whitespace_and_split(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (is_whitespace(str[i]))
			str[i] = ' ';
		i++;
	}
	return (ft_split(str, ' '));
}
