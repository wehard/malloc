/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:27:52 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/29 16:35:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

static void	*split_block(t_block *cur, size_t size)
{
	t_block	*free_block;

	free_block = (void *)cur + size + sizeof(t_block);
	free_block->size = cur->size - size - sizeof(t_block);
	free_block->next = cur->next;
	free_block->free = TRUE;
	free_block->data = NULL;
	cur->size = size;
	cur->free = FALSE;
	cur->data = (void *)cur + sizeof(t_block);
	cur->next = free_block;
	return (cur);
}

void	*get_block(size_t size, void *area)
{
	t_block	*cur;
	t_block	*prev;

	cur = area;
	while ((cur->size < size || cur->free == FALSE) && cur->next != NULL)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur->size == size)
	{
		cur->free = FALSE;
		cur->data = (void *)cur + sizeof(t_block);
		return (cur->data);
	}
	else if (cur->size > size + sizeof(t_block))
	{
		cur = split_block(cur, size);
		return (cur->data);
	}
	else
	{
		return (NULL);
	}
}
