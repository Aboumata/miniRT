/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:30:37 by abdahman          #+#    #+#             */
/*   Updated: 2025/10/16 10:54:18 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/miniRT.h"

void parse_sphere(t_scene *scene, char **token)
{
    t_sphere *sphere;

    sphere = new_sphere(token);
}

void parse_sphere(t_scene *scene, char **token)
{
    t_sphere *sphere;

    sphere = new_sphere(token);
}

void parse_line(t_scene *scene, char *line)
{
	char **token;

	token = ft_split(line, ' ');
	if (ft_strcmp("sp", token[0]) != 0)
		parse_sphere(scene, token);
}

void check_name(char *arg)
{
    size_t len;

    len = strlen(arg) - 3;
    if (strcmp(".rt", arg + len) != 0)
        exit((perror("invalid file name.\n"), 1));
}

void check_file_content(t_scene *scene, char *arg) {
    int fd;
    char *line;

    fd = open(arg, O_RDONLY);
    if (fd < 0)
        exit((perror("file not exist.\n"), 1));

    while ((line = get_next_line(fd)) != NULL)
    {
        parse_line(scene, line);
        free(line);
    }
    close(fd);
}

void parsing(t_scene *scene, char *arg)
{
    check_name(arg);
    check_file_content(scene, arg);
}
