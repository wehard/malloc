/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 21:23:28 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/26 21:49:21 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

void	print_memory(const void *addr, size_t size)
{
	size_t i;
	unsigned char *ptr;

	ptr = (unsigned char*)addr;

	i = 0;
	while (i < size)
	{
		ft_printf("%c", ptr[i]);
		if (i % 5 == 0)
			ft_printf(" ");
		if (i % 8 == 0)
			ft_printf("\n");
		i++;
	}
}
