/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:44:42 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/17 09:44:43 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int is_normalized (t_vector3 vec)
{
    double length;
    length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    if (length <  0.999 || length > 1.001)
        return 0;
    return 1;
}

void free_tokenizer(char **split)
{
    int i;

    i = 0;
    while (split[i]) {
        free(split[i]);
        i++;
    }
    free(split);
}

int count_tokens(char **token)
{
    int len;

    len = 0;
    while (token[len])
        len++;
    return (len);
}
