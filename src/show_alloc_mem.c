/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:30:08 by wkorande          #+#    #+#             */
/*   Updated: 2021/02/22 17:13:49 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "ft_printf.h"

static int	show_area(t_block *blocks, char *name)
{
	t_block	*cur;
	size_t	bytes;
	int		i;

	cur = blocks;
	bytes = 0;
	ft_printf("%s : %p\n", name, (void*)blocks);
	while (cur)
	{
		ft_printf("%p - %p : %d\t%s ",
			(void*)cur + sizeof(t_block), (void*)cur + sizeof(t_block) + cur->size,
			cur->size, cur->free == FALSE ? "USED" : "FREE");
		i = 0;
		while (i < (int)cur->size)
		{
			ft_putchar(*((char*)cur + sizeof(t_block) + i));
			i++;
		}
		ft_putchar('\n');
		if (cur->free == FALSE)
			bytes += cur->size;
		cur = cur->next;
	}
	return (bytes);
}

void		show_alloc_mem(void)
{
	size_t bytes;

	bytes = 0;
	bytes += show_area(g_malloc.tiny_blocks, "TINY");
	bytes += show_area(g_malloc.small_blocks, "SMALL");
	bytes += show_area(g_malloc.large_blocks, "LARGE");
	ft_printf("Total : %d bytes\n", bytes);
}
