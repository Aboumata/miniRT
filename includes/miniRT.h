/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:28:40 by abdahman          #+#    #+#             */
/*   Updated: 2025/10/18 18:41:00 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MINIRT_H
# define MINIRT_MINIRT_H

# include <stdlib.h>
#include "../minilibx-linux/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
#include "../get_next_line/get_next_line.h"
#include "../Libft/libft.h"

typedef enum e_obj_types
{
	SP,
	CY,
	PL
} t_obj_types;

typedef struct s_mem
{
	void *ptr;
	struct s_mem *next;
} t_mem;


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

typedef struct s_light {
	t_vector3 pos;
	double ratio;
	t_color color;
	struct s_light *next;
} t_light;

typedef struct s_spheres {
	t_vector3 center;
	double diameter;
	t_color color;
} t_spheres;

typedef struct s_planes {
	t_vector3 point;
	t_vector3 normal;
	t_color color;
} t_planes;

typedef struct s_ambient
{
	double ratio;
	t_color color;
} t_ambient;


typedef struct s_cylinders {
	t_vector3 center;
	t_vector3 dir;
	double diameter;
	double height;
	t_color color;
} t_cylinders;

typedef struct s_object
{
	t_obj_types type;
	void *obj;
	struct s_object *next;
} t_object;

typedef struct s_scene
{
	t_camera camera;
	t_ambient ambient;
	t_light *light;
	t_object *object;
	t_mem	*mem;

	int has_ambient;
	int has_camera;
} t_scene;

void parsing(t_scene *scene, char *arg);
void parse_sphere(t_scene *scene, char **token);
int new_sphere(t_object **obj, char **token);
t_vector3 parse_vec(char *token);
int count_tokens(char **token);
void ft_free_all(t_mem **mem);
void *ft_malloc(size_t size, t_mem **mem);
double ft_atof(char *str);
t_color parse_color(char *token);
void add_obj(t_scene *scene, void *ptr, t_obj_types type);
void parse_line(t_scene *scene, char *line);
void parse_plan(t_scene *scene, char **token);
void parse_ambient(t_scene *scene, char **token);
void parse_camera(t_scene *scene, char **token);
void parse_light (t_scene *scene, char **token);
void parse_cylinder (t_scene *scene, char **token);
void free_tokenizer(char **split);
int is_normalized (t_vector3 vec);
char **tokenize_line(char *line);
char **change_whitspace_and_split(char *str);

#endif
