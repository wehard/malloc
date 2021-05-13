/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:05:38 by wkorande          #+#    #+#             */
/*   Updated: 2021/05/13 16:00:32 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "malloc_internal.h"

// TODO: thread safety

void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*new;

	if (!ptr || !size)
		return (NULL);
	if (!ptr_is_valid(ptr))
		return (NULL);
	block = ptr - sizeof(t_block);
	if (size <= block->size)
	{
		block->size = size;
		return (ptr);
	}
	new = malloc(align_size(size));
	if (!new)
		return (NULL);
	ft_memcpy(new, ptr, block->size);
	free(ptr);
	return (new);
}
