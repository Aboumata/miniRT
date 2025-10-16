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

void check_name(char *arg)
{
	size_t len;

	len = strlen(arg) - 3;

	if (strcmp(".rt", arg + len) != 0)
		exit((perror("invalid file name.\n"), 1));
}



void check_file_content(char *arg)
{
	int fd;
	char *line;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
		exit((perror("file not exist.\n"), 1));
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line);
		free(line);
		line = get_next_line(fd);
	}
}

void parsing(char *arg)
{
	check_name(arg);
	check_file_content(arg);
}
