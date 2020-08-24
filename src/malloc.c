/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:03:29 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/24 23:34:18 by wkorande         ###   ########.fr       */
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
		// if (header->state == USED)
		// {
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
		// }
		ptr += sizeof(t_block_header) + header->size;
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
	char *ptr;

	if (g_malloc.initialized == FALSE)
		init_malloc();
	if (size <= g_malloc.tiny_size)
	{
		ptr = (char *)g_malloc.tiny_data;
		t_block_header *header = (t_block_header *)ptr;
		while (header->state == USED || (header->state == FREE && header->size > 0 && size > header->size))
		{
			ptr += sizeof(t_block_header) + header->size;
			header = (t_block_header *)ptr;
		}
		if (header->state == FREE)
		{
			int prev_size = header->size;
			header->state = USED;
			header->size = size;
			ft_printf("%*s[%d:%d][%0*d%s\n", ptr - (char *)g_malloc.tiny_data, "", header->state, header->size, header->size, 0, "]");
			ptr += sizeof(t_block_header);
			if (prev_size > 0)
			{
				t_block_header *tmp = (t_block_header *)(ptr + header->size);
				tmp->state = FREE;
				tmp->size = prev_size - size;
			}
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
	void *p;
	void *p1;

	p = ft_malloc(8);
	ft_strcpy(p, "01234567");

	p1 = ft_malloc(8);
	ft_strcpy(p1, "01234567");
	show_alloc_mem();

	ft_free(p);
	p1 = ft_malloc(2);
	show_alloc_mem();

	// ft_printf("%s\n", (char*)p);

	return (0);
}
