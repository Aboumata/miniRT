/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:26:19 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/15 19:26:20 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../miniRT.h"

void parse_line(t_scene *scene, char *line) {

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
