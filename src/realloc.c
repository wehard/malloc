/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:05:38 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/29 16:13:49 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "malloc_internal.h"
#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	new = ft_malloc(align_size(size));
	ft_memcpy(new, ptr, size);
	ft_free(ptr);
	return (new);
}
