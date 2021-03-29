/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:26:43 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/29 16:34:22 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"
#include <sys/mman.h>

void	init_heap(t_alloc_zone zone, t_block **blocks)
{
	size_t	heap_size;

	heap_size = calc_heap_size(zone);
	*blocks = create_heap(heap_size);
	(*blocks)->size = heap_size;
	(*blocks)->free = TRUE;
	(*blocks)->next = NULL;
}

void	*create_heap(size_t size)
{
	void	*new;

	new = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	return (new);
}

size_t	calc_heap_size(t_alloc_zone zone)
{
	size_t	heap_size;

	heap_size = 0;
	if (zone == TINY)
	{
		heap_size = ((((TINY_ALLOC_SIZE + sizeof(t_block)) * MAX_TINY)
					/ g_malloc.page_size) + 1) * g_malloc.page_size;
	}
	else if (zone == SMALL)
	{
		heap_size = ((((SMALL_ALLOC_SIZE + sizeof(t_block)) * MAX_SMALL)
					/ g_malloc.page_size) + 1) * g_malloc.page_size;
	}
	return (heap_size);
}

void	*get_heap(size_t size)
{
	if (!g_malloc.initialized)
		return (NULL);
	if (size <= TINY_ALLOC_SIZE)
	{
		if (!g_malloc.tiny_blocks)
			init_heap(TINY, &g_malloc.tiny_blocks);
		return (g_malloc.tiny_blocks);
	}
	else if (size <= SMALL_ALLOC_SIZE)
	{
		if (!g_malloc.small_blocks)
			init_heap(SMALL, &g_malloc.small_blocks);
		return (g_malloc.small_blocks);
	}
	else
		return (g_malloc.large_blocks);
}

void	*allocate_large(size_t size)
{
	t_block	*new;
	t_block	*cur;
	t_block	*prev;

	cur = g_malloc.large_blocks;
	prev = NULL;
	new = NULL;
	while (cur && cur->next)
	{
		prev = cur;
		cur = cur->next;
	}
	new = create_heap(size + sizeof(t_block));
	new->free = FALSE;
	new->size = size;
	new->next = NULL;
	new->data = (void *)new + sizeof(t_block);
	if (cur)
		cur->next = new;
	else
		cur = new;
	if (g_malloc.large_blocks == NULL)
		g_malloc.large_blocks = new;
	return (new->data);
}
