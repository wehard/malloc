/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:30:08 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/29 16:15:40 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"
#include "libft.h"
#include "ft_printf.h"

static void	show_debug(t_block	*cur)
{
	int	i;

	if (cur->free)
		ft_printf("\t%s ", "FREE");
	else
		ft_printf("\t%s ", "USED");
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
	ft_printf("%s : %p\n", name, (void *)blocks);
	while (cur && (debug || !cur->free))
	{
		ft_printf("%p - %p : %d bytes", (void *)cur + sizeof(t_block),
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
	bytes += show_area(g_malloc.tiny_blocks, "TINY", FALSE);
	bytes += show_area(g_malloc.small_blocks, "SMALL", FALSE);
	bytes += show_area(g_malloc.large_blocks, "LARGE", FALSE);
	ft_printf("Total : %d bytes\n", bytes);
}
