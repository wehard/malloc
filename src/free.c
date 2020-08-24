/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:05:16 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/24 21:43:22 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "ft_printf.h"

void ft_free(void *ptr)
{
	t_block_header *header;
	
	if (!ptr)
		return ;
	header = ptr - sizeof(t_block_header);
	if (header->state == USED)
		header->state = FREE;
	else
		ft_printf("malloc: pointer being freed was not allocated!\n");
}
