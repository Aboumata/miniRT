/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:41:29 by aboumata          #+#    #+#             */
/*   Updated: 2026/01/16 10:46:07 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	ft_perror(char **token, t_scene *scene, char *mes)
{
	if (token)
		free_split(token);
	if (scene && scene->mem)
		ft_free_all(&scene->mem);
	if (scene->mlx)
	{
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
		scene->mlx = NULL;
	}
	get_next_line(-1);
	if (mes)
		printf("%s", mes);
	exit(0);
}

static void	check_cylinder_token_count(t_scene *scene, char **token, int count)
{
	if (count < 6 || count > 8)
		ft_perror(token, scene, "Error: invalid cylinder\n");
}

static void	set_cylinder_defaults(t_cylinders *cylinder)
{
	cylinder->shininess = 0.0;
	cylinder->albedo_map = NULL;
	cylinder->bump_map = NULL;
}

static void	parse_cylinder_extras(t_scene *scene, char **token,
		t_cylinders *cylinder, int count)
{
	if (count >= 7)
	{
		cylinder->shininess = ft_atof(token[6], NULL);
		if (cylinder->shininess < 0)
			ft_perror(token, scene, "Error: invalid shininess\n");
	}
	if (count == 8)
	{
		cylinder->bump_map = load_texture(token[7], scene->mlx, &scene->mem);
		if (!cylinder->bump_map)
			ft_perror(token, scene, NULL);
	}
}

void	parse_cylinder(t_scene *scene, char **token)
{
	t_cylinders	*cylinder;
	int			count;

	count = count_tokens(token);
	check_cylinder_token_count(scene, token, count);
	cylinder = ft_malloc(sizeof(t_cylinders), &(scene->mem));
	cylinder->center = parse_vec(token, 1, scene);
	cylinder->diameter = ft_atof(token[3], NULL);
	cylinder->height = ft_atof(token[4], NULL);
	if (cylinder->diameter < 0 || cylinder->height < 0)
		ft_perror(token, scene,
			"Error: One of the diameter or height is not positive\n");
	cylinder->color = parse_color(token, 5, scene);
	cylinder->dir = parse_vec(token, 2, scene);
	if (!is_normalized(cylinder->dir))
		ft_perror(token, scene, "Error: cylinder direction not normalized\n");
	set_cylinder_defaults(cylinder);
	parse_cylinder_extras(scene, token, cylinder, count);
	add_obj(scene, cylinder, CY);
}
