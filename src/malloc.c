/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:03:29 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/30 10:39:27 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "malloc.h"
#include "malloc_internal.h"
#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <pthread.h>

/*
//	void *mmap(void *addr, size_t len,
//		int prot, int flags, int fd, off_t offset);
*/

t_malloc		g_malloc;
pthread_mutex_t	g_malloc_mutex;

void	init_malloc(void)
{
	g_malloc.page_size = getpagesize();
	g_malloc.heap_tiny = NULL;
	g_malloc.heap_small = NULL;
	g_malloc.heap_large = NULL;
	g_malloc.initialized = TRUE;
	pthread_mutex_init(&g_malloc_mutex, NULL);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (!g_malloc.initialized)
		init_malloc();
	size = align_size(size);
	pthread_mutex_lock(&g_malloc_mutex);
	if (size <= SMALL_ALLOC_SIZE)
		ptr = get_block(size, get_heap(size));
	else
		ptr = allocate_large(size);
	pthread_mutex_unlock(&g_malloc_mutex);
	return (ptr);
}

// int main(void)
// {
// 	void *tiny;
// 	void *small;
// 	void *large;
// 	// ft_printf("%d\n", x);
// 	tiny = ft_malloc(12);
// 	ft_strcpy(tiny, "hello world");
// 	small = ft_malloc(256);
// 	ft_strcpy(small, "..");
// 	large = ft_malloc(2048);
// 	ft_strcpy(large, "large allocation 2048 bytes");
// 	void *large2 = ft_malloc(4096);
// 	ft_strcpy(large2, "large allocation 4096 bytes");
// 	show_alloc_mem();
// 	// ft_free(tiny);
// 	ft_free(tiny);
// 	ft_free(small);
// 	ft_free(large);
// 	ft_free(large2);
// 	ft_printf("\n");
// 	show_alloc_mem();
// 	// print_memory(a, 2);
// 	return (0);
// }
