/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:30:08 by wkorande          #+#    #+#             */
/*   Updated: 2021/02/22 18:19:36 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "ft_printf.h"

static int	show_area(t_block *blocks, char *name, int debug)
{
	t_block	*cur;
	size_t	bytes;
	int		i;

	cur = blocks;
	bytes = 0;
	ft_printf("%s : %p\n", name, (void*)blocks);
	while (cur && (debug || !cur->free))
	{
		ft_printf("%p - %p : %d bytes", (void*)cur + sizeof(t_block), (void*)cur + sizeof(t_block) + cur->size, cur->size);
		if (debug)
		{
			ft_printf("\t%s ", cur->free == FALSE ? "USED" : "FREE");
			i = 0;
			while (i < (int)cur->size)
			{
				ft_putchar(*((char*)cur + sizeof(t_block) + i));
				i++;
			}
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
	bytes += show_area(g_malloc.tiny_blocks, "TINY", FALSE);
	bytes += show_area(g_malloc.small_blocks, "SMALL", FALSE);
	bytes += show_area(g_malloc.large_blocks, "LARGE", FALSE);
	ft_printf("Total : %d bytes\n", bytes);
}