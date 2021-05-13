/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:30:08 by wkorande          #+#    #+#             */
/*   Updated: 2021/05/13 14:09:30 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"
#include <stdio.h>

static void	show_debug(t_block	*cur)
{
	int	i;

	if (cur->free)
		printf("\t%s ", "FREE");
	else
		printf("\t%s ", "USED");
	i = 0;
	while (i < (int)cur->size)
	{
		ft_putchar(*((char *)cur + sizeof(t_block) + i));
		i++;
	}
}

static int	show_area(t_block *blocks, char *name, int debug)
{
	t_block	*cur;
	size_t	bytes;

	cur = blocks;
	bytes = 0;
	printf("%s : %p\n", name, (void *)blocks);
	while (cur && (debug || !cur->free))
	{
		printf("%p - %p : %ld bytes", (void *)cur + sizeof(t_block),
			(void *)cur + sizeof(t_block) + cur->size, cur->size);
		if (debug)
			show_debug(cur);
		ft_putchar('\n');
		if (cur->free == FALSE)
			bytes += cur->size;
		cur = cur->next;
	}
	return (bytes);
}

void	show_alloc_mem(void)
{
	size_t	bytes;

	bytes = 0;
	bytes += show_area(g_malloc.heap_tiny, "TINY", FALSE);
	bytes += show_area(g_malloc.heap_small, "SMALL", FALSE);
	bytes += show_area(g_malloc.heap_large, "LARGE", FALSE);
	printf("Total : %ld bytes\n", bytes);
}

void	show_alloc_mem_ex(void)
{
	size_t	bytes;

	bytes = 0;
	bytes += show_area(g_malloc.heap_tiny, "TINY", TRUE);
	bytes += show_area(g_malloc.heap_small, "SMALL", TRUE);
	bytes += show_area(g_malloc.heap_large, "LARGE", TRUE);
	printf("Total : %ld bytes\n", bytes);
}
