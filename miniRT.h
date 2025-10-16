/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:22:21 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/15 19:22:22 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINIRT_MINIRT_H
# define MINIRT_MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
<<<<<<< HEAD
# include "Libft/libft.h"

typedef struct space
{
	t_camira *camira;
=======
# include "libft/libft.h"

typedef struct space
{
    t_camira *camira;
    t_a
>>>>>>> origin/main
};


void parsing(char *arg);

#endif

