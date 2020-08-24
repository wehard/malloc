/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:03:29 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/24 17:16:44 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>

//  void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);

t_malloc g_malloc;

void	show_alloc_mem(void)
{

	ft_printf("TINY : %p\n", g_malloc.tiny_data);
	char *ptr = g_malloc.tiny_data;
	char state = *(char*)(ptr);
	while (ptr < (char*)g_malloc.tiny_data + g_malloc.tiny_size - 1)
	{
		state = *(char*)(ptr);
		ptr += 1;
		int b_size = (int)*ptr;
		if (state == USED)
		{
			ft_printf("%p - %p : %d\n", ptr + sizeof(int), ptr + sizeof(int) + b_size, b_size);
		}
		ptr += sizeof(int);
		ptr += b_size;
	}

}

void init_malloc()
{
	g_malloc.page_size = getpagesize();
	ft_printf("page size: %d\n", g_malloc.page_size);
	g_malloc.tiny_size = TINY * g_malloc.page_size;
	g_malloc.tiny_data = mmap(0, g_malloc.tiny_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	int i = 0;
	ft_bzero(g_malloc.tiny_data, g_malloc.tiny_size);
	while (i < NUM_TINY)
	{
		g_malloc.tiny_allocs[i].state = FREE;
		g_malloc.tiny_allocs[i].area = TINY;
		g_malloc.tiny_allocs[i].ptr = NULL;
		g_malloc.tiny_allocs[i].size = 0;
		i++;
	}
	g_malloc.initialized = TRUE;
}

void *ft_malloc(size_t size)
{
	if (g_malloc.initialized == FALSE)
		init_malloc();
	if (size <= g_malloc.tiny_size)
	{
		// find first free spot where allocation fits
		char *ptr = g_malloc.tiny_data;
		char state = *(char*)(ptr);
		while (state == USED)
		{
			ptr += 1;
			int b_size = (int)*ptr;
			ptr += sizeof(int);
			ptr += b_size;
			state = *(char*)(ptr);
		}
		if (state == FREE)
		{
			*ptr = USED;
			ptr += 1;
			*(int*)ptr = (int)size;
			ptr += sizeof(int);
			ft_printf("allocated tiny: %d bytes at %p\n", size, ptr);
			return (ptr);
		}

	}
	size = 0;
	return (NULL);
}

int main(void)
{
	void *p;
	void *p1;
	void *p2;

	p = ft_malloc(8);
	p1 = ft_malloc(16);
	p2 = ft_malloc(32);
	show_alloc_mem();

	ft_free(p1);
	p1 = ft_malloc(8);
	show_alloc_mem();

	// ft_strcpy(p, "hello");
	// ft_printf("%s\n", (char*)p);

	return (0);
}
