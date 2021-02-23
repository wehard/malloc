/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:03:29 by wkorande          #+#    #+#             */
/*   Updated: 2021/02/23 17:09:51 by wkorande         ###   ########.fr       */
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

void init_malloc()
{
	g_malloc.page_size = getpagesize();

	size_t tiny_total_size = g_malloc.page_size * NUM_TINY_PAGES;

	g_malloc.tiny_data = mmap(0, tiny_total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	g_malloc.tiny_blocks = g_malloc.tiny_data;
	g_malloc.tiny_blocks->size = tiny_total_size - sizeof(t_block);
	g_malloc.tiny_blocks->free = TRUE;
	g_malloc.tiny_blocks->next = NULL;

	size_t small_total_size = g_malloc.page_size * NUM_SMALL_PAGES;

	g_malloc.small_data = mmap(0, small_total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	g_malloc.small_blocks = g_malloc.small_data;
	g_malloc.small_blocks->size = small_total_size - sizeof(t_block);
	g_malloc.small_blocks->free = TRUE;
	g_malloc.small_blocks->next = NULL;

	g_malloc.large_blocks = NULL;

	g_malloc.initialized = TRUE;

	ft_printf("initialized (%d bytes)\n", tiny_total_size + small_total_size);
}

void *split_block(t_block *cur, size_t size)
{
	t_block *free_block;

	free_block = (void*)cur + size + sizeof(t_block);
	free_block->size = cur->size - size - sizeof(t_block);
	free_block->next = cur->next;
	free_block->free = TRUE;
	free_block->data = NULL;

	cur->size =  size;
	cur->free = FALSE;
	cur->data = (void*)cur + sizeof(t_block);
	cur->next = free_block;
	return (cur);
}

void *allocate_area(size_t size, void *area)
{
	t_block *cur;
	t_block *prev;
	
	cur = area;

	while ((cur->size < size || cur->free == FALSE) && cur->next != NULL)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur->size == size)
	{
		cur->free = FALSE;
		cur->data = (void*)cur + sizeof(t_block);
		return (cur->data);
	}
	else if (cur->size > size + sizeof(t_block))
	{
		cur = split_block(cur, size);
		return (cur->data);
	}
	else
	{
		ft_printf("Failed to allocate memory!\n");
		return (NULL);
	}
}

void *allocate_large(size_t size)
{
	t_block *new;
	t_block *cur;
	t_block *prev;

	cur = g_malloc.large_blocks;
	prev = NULL;
	new = NULL;

	while (cur && cur->next)
	{
		prev = cur;
		cur = cur->next;
	}

	new = mmap(0, size + sizeof(t_block), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	new->free = FALSE;
	new->size = size;
	new->next = NULL;
	new->data = new + 1;

	if (cur)
		cur->next = new;
	else
		cur = new;

	if (g_malloc.large_blocks == NULL)
		g_malloc.large_blocks = new;

	return (new->data);
}

void *ft_malloc(size_t size)
{
	if (!g_malloc.initialized)
		init_malloc();

	if (size <= TINY_ALLOC_SIZE)
		return (allocate_area(size, g_malloc.tiny_blocks));
	else if (size <= SMALL_ALLOC_SIZE)
		return (allocate_area(size, g_malloc.small_blocks));
	else
		return (allocate_large(size));
	ft_printf("Out of memory!\n");
	return (NULL);
}
/* 
int main(void)
{
	void *tiny;
	void *small;
	void *large;

	tiny = ft_malloc(12);
	ft_strcpy(tiny, "hello world");

	small = ft_malloc(256);
	ft_strcpy(small, "..");

	large = ft_malloc(2048);
	ft_strcpy(large, "large allocation 2048 bytes");

	void *large2 = ft_malloc(4096);
	ft_strcpy(large2, "large allocation 4096 bytes");
	
	show_alloc_mem();

	// ft_free(tiny);
	ft_free(tiny);
	ft_free(small);
	ft_free(large);
	ft_free(large2);
	ft_printf("\n");

	show_alloc_mem();

	// print_memory(a, 2);
	
	return (0);
} */
