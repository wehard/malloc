/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:03:29 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/26 00:21:54 by wkorande         ###   ########.fr       */
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

void show_alloc_mem(void)
{
	char *ptr;

	ft_printf("TINY : %p\n", g_malloc.tiny_data);
	ptr = g_malloc.tiny_data;
	while (ptr < (char *)(g_malloc.tiny_data + 128 /*g_malloc.tiny_size*/))
	{
		t_block_header *header = (t_block_header *)ptr;
		// while (header->state == FREE && header->size == 0)
		// 	ptr++;
		ft_printf("%d ", sizeof(t_block_header));
		char *block_start = ptr + sizeof(t_block_header);
		char *block_end = block_start + header->size;
		ft_printf("%p - %p : %d\t%s ", block_start, block_end, (block_end - block_start), header->state == USED ? "USED" : "FREE");
		int i = 0;
		while (i < (int)header->size)
		{
			ft_putchar(block_start[i]);
			i++;
		}
		ft_putchar('\n');
		ptr += sizeof(t_block_header) + header->size;
	}
}

void init_malloc()
{
	g_malloc.page_size = getpagesize();
	ft_printf("page size: %d\n", g_malloc.page_size);
	g_malloc.tiny_size = TINY * g_malloc.page_size;
	g_malloc.tiny_left = g_malloc.tiny_size;
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
	char *ptr;

	if (g_malloc.initialized == FALSE)
		init_malloc();
	if (size < g_malloc.tiny_left - sizeof(t_block_header))
	{
		ptr = (char *)g_malloc.tiny_data;
		t_block_header *header = (t_block_header *)ptr;
		while (header->state == USED || (header->state == FREE && header->size > 0 && size > header->size + sizeof(t_block_header)))
		{
			ptr += sizeof(t_block_header) + header->size;
			header = (t_block_header *)ptr;
		}
		if (header->state == FREE)
		{
			if (header->size > size + sizeof(t_block_header))
			{
				// we can partition the block of memory
				ft_printf("partitioning\n");
			}
			int prev_size = header->size;
			int remaining_size = header->size - sizeof(t_block_header) - size;
			header->state = USED;
			header->size = size;
			ft_printf("%*s[%d:%d][%0*d%s\n", ptr - (char *)g_malloc.tiny_data, "", header->state, header->size, header->size, 0, "]");
			ptr += sizeof(t_block_header);
			t_block_header *tmp = (t_block_header *)(ptr + header->size);
			if (remaining_size > 1)
			{
				tmp->state = FREE;
				tmp->size = prev_size - size;
			}
			// else
			// 	ft_bzero(tmp, sizeof(t_block_header) + remaining_size);
			// ft_printf("allocated tiny: %d bytes at %p\n", size, ptr);
			return (ptr);
		}
		else
			ft_printf("something went wrong\n");
	}
	size = 0;
	return (NULL);
}

int main(void)
{
	void *a;
	void *b;
	void *c;

	a = ft_malloc(8);
	ft_strcpy(a, "aaa");

	b = ft_malloc(8);
	ft_strcpy(b, "bbb");

	c = ft_malloc(8);
	ft_strcpy(c, "ccc");
	
	ft_free(b);
	b = ft_malloc(8);
	ft_strcpy(b, "xxx");
	show_alloc_mem();
	// ft_free(p);
	// show_alloc_mem();

	// ft_printf("%s\n", (char*)p);

	return (0);
}
