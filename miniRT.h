/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:22:21 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/16 10:52:53 by abdahman         ###   ########.fr       */
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
# include "Libft/libft.h"

typedef struct s_vector3
{
    double x;
    double y;
    double z;
} t_vector3;

typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_camera
{
    t_vector3 pos;
    t_vector3 dir;
    double    fov;
} t_camera;

typedef struct s_ambient
{
    double ratio;
    t_color color;
} t_ambient;

typedef struct s_sphere
{
    t_vector3 center;
    double diameter;
    t_color color;
} t_sphere;

typedef struct s_scene
{
    t_camera camera;
    t_ambient ambient;
} t_scene;

void parsing(t_scene *scene, char *arg);

#endif

