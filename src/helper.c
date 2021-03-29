/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:26:00 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/29 16:26:22 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

int	ptr_is_valid(void *ptr)
{
	t_block	*cur;

	cur = g_malloc.tiny_blocks;
	while (cur)
	{
		if (cur->data && cur->data == ptr)
			return (TRUE);
		cur = cur->next;
	}
	cur = g_malloc.small_blocks;
	while (cur)
	{
		if (cur->data && cur->data == ptr)
			return (TRUE);
		cur = cur->next;
	}
	cur = g_malloc.large_blocks;
	while (cur)
	{
		if (cur->data && cur->data == ptr)
			return (TRUE);
		cur = cur->next;
	}
	return (FALSE);
}

size_t	align_size(size_t size)
{
	return ((size + 15) & ~15);
}
