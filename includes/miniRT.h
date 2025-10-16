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
#include "../get_next_line/get_next_line.h"
#include "../Libft/libft.h"

typedef struct s_vector3
{
    double x;
    double y;
    double z;
} t_vector3;

typedef struct s_colors
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

typedef struct s_lights {
    t_vector3 pos;
    double ratio;
    t_color color;
    struct s_lights *next;
} t_lights;

typedef struct s_spheres {
    t_vector3 center;
    double diameter;
    t_color color;
    struct s_spheres *next;
} t_spheres;

typedef struct s_planes {
    t_vector3 point;
    t_vector3 normal;
    t_color color;
    struct s_planes *next;
} t_planets;

typedef struct s_ambient
{
    double ratio;
    t_color color;
} t_ambient;

typedef struct s_cylinders {
    t_vector3 center;
    t_vector3 dir;
    double diameter;
    double hight;
    t_color color;
    struct s_cylinders *next;
} t_cylinders;

typedef struct s_scene
{
    t_camera camera;
    t_ambient ambient;
    t_lights *lights;
    t_cylinders *cylinders;
    t_planets *planets;
    t_spheres *spheres;

    int has_ambient;
    int has_camera;
    int has_light;
} t_scene;

void parsing(t_scene *scene, char *arg);

#endif

