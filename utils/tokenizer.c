/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:27:15 by aboumata          #+#    #+#             */
/*   Updated: 2025/10/18 16:53:36 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return 1;
	return 0;
}

// static char *skip_whitespace(char *str)
// {
// 	while (is_whitespace(*str))
// 		str++;
// 	return (str);
// }

// static size_t get_token_length(char *str)
// {
// 	int length;

// 	length = 0;
// 	while (!is_whitespace(*str) && *str) //radi tw9af fi awal whire space !!!
// 	{
// 		length++;
// 		str++;
// 	}
// 	return (length);
// }

// static int count_tokens_of_line(char *line)
// {
// 	int count;
// 	char *current;
// 	size_t len;

// 	count = 0;
// 	current = line;
// 	while (*current != '\0')
// 	{
// 		current = skip_whitespace(current);
// 		if (*current == '\0')
// 			break;
// 		len = get_token_length(current);
// 		if (len > 0)
// 		{
// 			count++;
// 			current += len;
// 		}
// 	}
// 	return (count);
// }

// char **tokenize_line(char *line)
// {
// 	char **tokens;
// 	char *current;
// 	int index;
// 	size_t length;
// 	int token_count;

// 	if (!line || line[0] == '\0' || line[0] == '\n')
// 		return NULL;
// 	token_count = count_tokens_of_line(line);
// 	if (token_count == 0)
// 		return NULL;
// 	tokens = malloc(sizeof(char *) * (token_count + 1));
// 	if (!tokens)
// 		return (NULL);
// 	index = 0;
// 	current = line;
// 	while (*current != '\0')
// 	{
// 		current = skip_whitespace(current);
// 		if (*current == '\0')
// 			break;
// 		length = get_token_length(current);
// 		tokens[index] = ft_substr(current, 0, length);
// 		if (!tokens[index])
// 		{
// 			while (index > 0)
// 				free(tokens[--index]);
// 			free(tokens);
// 			return (NULL);
// 		}
// 		index++;
// 		current += length;
// 	}
// 	tokens[index] = NULL;
// 	return (tokens);
// }

char **change_whitespace_and_split(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (is_whitespace(str[i]))
			str[i] = ' ';
		i++;
	}
	return(ft_split(str, ' '));
}
