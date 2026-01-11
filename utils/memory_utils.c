/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdahman <abdahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:45:34 by abdahman          #+#    #+#             */
/*   Updated: 2026/01/11 09:59:56 by abdahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	ft_free_all(t_mem **mem)
{
	t_mem	*tmp;
	t_mem	*node;

	if (!mem || !*mem)
		return ;
	tmp = *mem;
	get_next_line(-1);
	while (tmp)
	{
		node = tmp;
		tmp = tmp->next;
		free(node->ptr);
		free(node);
	}
	*mem = NULL;
}

void	cleanup_all(t_data *data)
{
	if (!data)
		return ;
	cleanup_mlx(data);
	if (data->scene)
		ft_free_all(&data->scene->mem);
}

void	*ft_malloc(size_t size, t_mem **mem)
{
	void	*ptr;
	t_mem	*node;

	ptr = malloc(size);
	if (!ptr)
		exit((perror("malloc filed."), 1));
	node = malloc(sizeof(t_mem));
	if (!node)
		exit((perror("malloc filed."), 1));
	node->ptr = ptr;
	node->next = *mem;
	*mem = node;
	return (ptr);
}
