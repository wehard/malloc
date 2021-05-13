/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:05:16 by wkorande          #+#    #+#             */
/*   Updated: 2021/05/13 13:23:09 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"
#include "ft_printf.h"
#include <sys/mman.h>

static void	unmap_heap(t_block **area)
{
	if (munmap((void *)*area, (*area)->size + sizeof(t_block) != 0))
		ft_printf("failed to unmap\n");
}

static int	release_block(void *ptr, t_block **area)
{
	t_block	*cur;
	// t_block	*prev;

	cur = *area;
	// prev = NULL;
	while (cur)
	{
		if (cur->data && cur->data == ptr)
		{
			if (cur->next->free)
			{
				cur->size += cur->next->size;
				cur->next = cur->next->next;
			}
			cur->free = TRUE;
			cur->data = NULL;
			if (cur->free && !cur->next)
			{
				unmap_heap(area);
				*area = NULL;
			}
			return (TRUE);
		}
		// prev = cur;
		cur = cur->next;
	}
	return (FALSE);
}

static int	release_large_block(void *ptr, t_block **area)
{
	t_block	*cur;
	t_block	*prev;

	cur = *area;
	prev = NULL;
	while (cur)
	{
		if (cur->data && cur->data == ptr)
		{
			if (!prev)
			{
				*area = cur->next;
				unmap_heap(&cur);
			}
			else
			{
				prev->next = cur->next;
				unmap_heap(&cur);
			}
			return (TRUE);
		}
		prev = cur;
		cur = cur->next;
	}
	return (FALSE);
}

void	free(void *ptr)
{
	if (!ptr)
		return ;
	if (release_block(ptr, &g_malloc.heap_tiny))
		return ;
	if (release_block(ptr, &g_malloc.heap_small))
		return ;
	if (release_large_block(ptr, &g_malloc.heap_large))
		return ;
}
