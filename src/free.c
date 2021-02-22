/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:05:16 by wkorande          #+#    #+#             */
/*   Updated: 2021/02/22 17:04:19 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "ft_printf.h"
#include <sys/mman.h>

static int release_block(void *ptr, t_block **area)
{
	t_block *cur;
	t_block *prev;

	if (!ptr)
		return (FALSE);
	
	cur = *area;
	prev = NULL;

	while (cur)
	{
		if (cur->data == ptr)
		{
			// free memory
			if (!prev) // its the first block
			{
				*area = cur->next;
				munmap((void*)cur, cur->size + sizeof(t_block));
			}
			else
			{
				prev->next = cur->next;
				munmap((void*)cur, cur->size + sizeof(t_block));
			}
			return (TRUE);
		}
		prev = cur;
		cur = cur->next;
	}
	return (FALSE);
}

void ft_free(void *ptr)
{
	if (release_block(ptr, &g_malloc.tiny_blocks))
		return ;
	if (release_block(ptr, &g_malloc.small_blocks))
		return ;
	if (release_block(ptr, &g_malloc.large_blocks))
		return ;
}
