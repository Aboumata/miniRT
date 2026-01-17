/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:28:40 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/17 10:02:26 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../Libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265359
# define EPSILON 0.0001

typedef struct s_texture
{
	int			width;
	int			height;
	char		*data;
	char		*path;
	void		*img;
	int			bpp;
	int			line_len;
	int			endian;
} 			t_texture;

typedef struct s_uv
{
	double	u;
	double	v;
}			t_uv;

typedef enum e_obj_types
{
	SP,
	CY,
	PL,
	CONE,
	TRIANGLE,
	DISK
}					t_obj_types;

typedef struct s_mem
{
	void			*ptr;
	struct s_mem	*next;
}					t_mem;

typedef struct s_vector3
{
	double			x;
	double			y;
	double			z;
}					t_vector3;

typedef struct s_colors
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_camera
{
	t_vector3		pos;
	t_vector3		dir;
	double			fov;
}					t_camera;

typedef struct s_light
{
	t_vector3		pos;
	double			ratio;
	t_color			color;
	struct s_light	*next;
}					t_light;

typedef struct s_spheres
{
	t_vector3		center;
	double			diameter;
	t_color			color;
	double			shininess;
	int				checkerboard;
	t_texture		*albedo_map;
	t_texture		*bump_map;
}					t_spheres;

typedef struct s_planes
{
	t_vector3		point;
	t_vector3		normal;
	t_color			color;
	double			shininess;
	int				checkerboard;
	t_texture		*albedo_map;
	t_texture		*bump_map;
}					t_planes;

typedef struct s_cone
{
	t_vector3		center;
	t_vector3		dir;
	double			diameter;
	double			height;
	t_color			color;
}					t_cone;

typedef struct s_triangle
{
	t_vector3		p1;
	t_vector3		p2;
	t_vector3		p3;
	t_color			color;
}					t_triangle;

typedef struct s_disk
{
	t_vector3		center;
	t_vector3		normal;
	double			diameter;
	t_color			color;
}					t_disk;

typedef struct s_ambient
{
	double			ratio;
	t_color			color;
}					t_ambient;

typedef struct s_cylinders
{
	t_vector3		center;
	t_vector3		dir;
	double			diameter;
	double			height;
	t_color			color;
	double			shininess;
	int				checkerboard;
	t_texture		*albedo_map;
	t_texture		*bump_map;
}					t_cylinders;

typedef struct s_object
{
	t_obj_types		type;
	void			*obj;
	struct s_object	*next;
}					t_object;

typedef struct s_scene
{
	t_camera		camera;
	t_ambient		ambient;
	t_light			*light;
	t_object		*object;
	t_mem			*mem;
	void			*mlx;
	int				has_ambient;
	int				has_camera;
}					t_scene;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_mlx;

typedef struct s_atof
{
	double			res;
	double			frac;
	double			div;
	int				dot_count;
}					t_atof;

typedef struct s_ray
{
	t_vector3		origin;
	t_vector3		direction;
}					t_ray;

typedef struct s_camera_data
{
	t_vector3		forward;
	t_vector3		right;
	t_vector3		up;

	double			viewport_width;
	double			viewport_height;

	t_vector3		viewport_center;
	t_vector3		top_left;
}					t_camera_data;

typedef struct s_data
{
	t_scene			*scene;
	t_mlx			mlx;
	t_camera_data	cam;
}					t_data;

typedef struct s_hit
{
	int				hit;
	double			t;
	t_vector3		point;
	t_vector3		normal;
	t_color			color;
	void			*object;
	t_obj_types		type;
	double			shininess;
}					t_hit;

typedef struct s_variables
{
	t_vector3	edgs[2];
	t_vector3	oc;
	t_vector3	hit_point;
	double		t;
	t_hit		*hit;
	t_ray		ray;
}				t_variables;

void				parsing(t_scene *scene, char *arg);
void				parse_sphere(t_scene *scene, char **token);
t_vector3			parse_vec(char **token, int indx, t_scene *scene);
int					count_tokens(char **token);
void				ft_free_all(t_mem **mem);
void				*ft_malloc(size_t size, t_mem **mem);
double				ft_atof(char *str, int *check);
t_color				parse_color(char **token, int indx, t_scene *scene);
void				add_obj(t_scene *scene, void *ptr, t_obj_types type);
void				parse_line(t_scene *scene, char *line);
void				parse_plan(t_scene *scene, char **token);
void				parse_ambient(t_scene *scene, char **token);
void				parse_camera(t_scene *scene, char **token);
void				parse_light(t_scene *scene, char **token);
void				parse_cylinder(t_scene *scene, char **token);
void				parse_cone(t_scene *scene, char **token);
void				parse_triangle(t_scene *scene, char **token);
void				parse_disk(t_scene *scene, char **token);
void				free_split(char **split);
int					is_normalized(t_vector3 vec);
char				**change_whitespace_and_split(char *str);
void				cleanup_mlx(t_data *data);
int					initialize_mlx(t_data *data);
int					create_color(int r, int g, int b);
void				put_pixel(t_data *data, int x, int y, int color);
int					handle_key(int keycode, t_data *data);
int					handle_close(t_data *data);
void				setup_hooks(t_data *data);
void				render(t_data *data);
t_vector3			vec_add(t_vector3 a, t_vector3 b);
t_vector3			vec_sub(t_vector3 a, t_vector3 b);
t_vector3			vec_scale(t_vector3 v, double scalar);
double				vec_length(t_vector3 v);
t_vector3			vec_normalize(t_vector3 v);
double				vec_dot(t_vector3 a, t_vector3 b);
t_vector3			vec_cross(t_vector3 a, t_vector3 b);
t_vector3			vec_reflect(t_vector3 v, t_vector3 n);
void				setup_camera(t_data *data);
t_ray				create_ray(t_data *data, int x, int y);
t_vector3			ray_at(t_ray ray, double t);
void				init_hit(t_hit *hit);
int					is_closer_hit(t_hit *current, double new_t);
void				update_hit(t_variables *var, t_vector3 normal,
						t_color color);
int					intersect_sphere(t_ray ray, t_spheres *sphere, t_hit *hit);
void				test_sphere_intersection(t_data *data);
t_color				calculate_lighting(t_hit *hit, t_scene *scene);
int					is_in_shadow(t_vector3 point, t_vector3 normal,
						t_vector3 light_pos, t_scene *scene);
int					intersect_plane(t_ray ray, t_planes *plane, t_hit *hit);
t_color				get_checkerboard_color(t_uv uv);
int					intersect_cylinder(t_ray ray, t_cylinders *cylinder,
						t_hit *hit);
int					intersect_disk(t_ray ray, t_disk *disk, t_hit *hit);
int					intersect_triangle(t_ray ray, t_triangle *triangle,
						t_hit *hit);
int					intersect_cone(t_ray ray, t_cone *cone, t_hit *hit);
t_color				color_multiply(t_color a, t_color b);
t_color				color_scale(t_color color, double ratio);
t_color				color_add(t_color a, t_color b);
t_color				calculate_ambient(t_ambient ambient, t_color obj_color);
void				ft_perror(char **token, t_scene *scene, char *mes);
t_texture			*load_texture(char *path, void *mlx, t_mem **mem);
int					get_texture_color(t_texture *tex, int x, int y);
double				get_bump_height(t_texture *bump, double u, double v);
t_color				sample_texture_color(t_texture *tex, t_uv uv);
t_uv				sphere_uv(t_vector3 point, t_vector3 center);
t_uv				plane_uv(t_vector3 point, t_vector3 plane_point);
t_uv				cylinder_uv(t_vector3 point, t_cylinders *cyl);
t_vector3			perturb_normal(t_vector3 normal, t_texture *bump, t_uv uv);
void				destroy_texture(void *mlx, t_texture *tex);
void				destroy_scene_textures(t_scene *scene, void *mlx);
double				clamp(double x, double a, double b);
double				clamp01(double x);
double				wrap01(double x);

#endif
