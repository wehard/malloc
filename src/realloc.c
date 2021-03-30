/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:05:38 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/30 15:17:09 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "malloc_internal.h"
#include "libft.h"

// TODO: thread safety

void	*ft_realloc(void *ptr, size_t size)
{
	t_block *block;
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
	if (!(new = ft_malloc(align_size(size))))
		return (NULL);
	ft_memcpy(new, ptr, block->size);
	ft_free(ptr);
	return (new);
}
