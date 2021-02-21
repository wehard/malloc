/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:03:29 by wkorande          #+#    #+#             */
/*   Updated: 2021/02/21 23:54:33 by wkorande         ###   ########.fr       */
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
	t_block *cur;

	cur = g_malloc.blocks;

	ft_printf("TINY : %p\n", g_malloc.data);

	while (cur)
	{
		ft_printf("%p - %p : %d\t%s ", cur + sizeof(t_block), cur + sizeof(t_block) + cur->size, cur->size, cur->free == FALSE ? "USED" : "FREE");
			int i = 0;
		while (i < (int)cur->size)
		{
			ft_putchar(*((char*)cur + sizeof(t_block) + i));
			i++;
		}
		ft_putchar('\n');
		cur = cur->next;
	}
}

void init_malloc()
{
	g_malloc.page_size = getpagesize();

	size_t data_size = g_malloc.page_size;

	g_malloc.data = mmap(0, data_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	g_malloc.blocks = g_malloc.data;
	g_malloc.blocks->size = data_size - sizeof(t_block);
	g_malloc.blocks->free = TRUE;
	g_malloc.blocks->next = NULL;

	g_malloc.initialized = TRUE;

	ft_printf("initialized (%d bytes)\n", data_size);
}

void split_block(t_block *cur, size_t size)
{
	t_block *free_block;

	free_block = (void*)cur + size + sizeof(t_block);
	free_block->size = cur->size - size - sizeof(t_block);
	free_block->next = cur->next;
	free_block->free = TRUE;

	cur->size =  size;
	cur->free = FALSE;
	cur->next = free_block;
}

void *ft_malloc(size_t size)
{
	t_block *cur;
	t_block *prev;
	
	if (!g_malloc.initialized)
		init_malloc();

	cur = g_malloc.blocks;

	while ((cur->size < size || cur->free == FALSE) && cur->next != NULL)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur->size == size)
	{
		cur->free = FALSE;
		return (cur + 1);
	}
	else if (cur->size > size + sizeof(t_block))
	{
		split_block(cur, size);
		return (cur + 1);
	}
	else
	{
		ft_printf("Failed to allocate memory!\n");
		return (NULL);
	}
}

int main(void)
{
	void *a;
	void *b;
	void *c;

	a = ft_malloc(2);
	ft_strcpy(a, "..");

	b = ft_malloc(2);
	ft_strcpy(b, "xx");

	c = ft_malloc(20);
	ft_strcpy(c, "!!");
	
	show_alloc_mem();

	print_memory(a, 24);
	
	return (0);
}
