/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:05:16 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/24 17:01:17 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "ft_printf.h"

void ft_free(void *ptr)
{
	char state;

	if (!ptr)
		return ;
	ptr -= sizeof(int) + 1;
	state = *(char*)(ptr);
	if (state == USED)
		*(char*)ptr = FREE;
	else
		ft_printf("malloc: pointer being freed was not allocated!\n");
}
