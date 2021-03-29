/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:05:16 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/29 16:16:01 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"
#include "ft_printf.h"
#include <sys/mman.h>

static int	release_block(void *ptr, t_block **area)
{
	t_block	*cur;
	t_block	*prev;

	cur = *area;
	prev = NULL;
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
				if (munmap((void *)*area, cur->size + sizeof(t_block) != 0))
					ft_printf("failed to unmap\n");
				*area = NULL;
			}
			return (TRUE);
		}
		prev = cur;
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
				munmap((void *)cur, cur->size + sizeof(t_block));
			}
			else
			{
				prev->next = cur->next;
				munmap((void *)cur, cur->size + sizeof(t_block));
			}
			return (TRUE);
		}
		prev = cur;
		cur = cur->next;
	}
	return (FALSE);
}

void	ft_free(void *ptr)
{
	if (!ptr)
		return ;
	if (release_block(ptr, &g_malloc.tiny_blocks))
		return ;
	if (release_block(ptr, &g_malloc.small_blocks))
		return ;
	if (release_large_block(ptr, &g_malloc.large_blocks))
		return ;
}
