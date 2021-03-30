/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc_large.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/30 10:39:29 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "malloc.h"
#include "malloc_internal.h"
#include "libft.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void single_allocation(void)
{
	char *block = (char *)ft_malloc(SMALL_ALLOC_SIZE + 1);
	ft_strncpy(block, "hello world", 12);
	TEST_ASSERT_NOT_NULL(block);
	TEST_ASSERT_EQUAL_CHAR('h', block[0]);
	TEST_ASSERT_EQUAL_CHAR('d', block[10]);
	ft_free(block);
}

void verify_alloc_info(void)
{
	size_t size = align_size(SMALL_ALLOC_SIZE + 1);
	void *ptr = ft_malloc(size);
	t_block *block = ptr - sizeof(t_block);

	TEST_ASSERT_NOT_NULL(ptr);
	TEST_ASSERT_NOT_NULL(block);
	TEST_ASSERT_EQUAL_PTR(ptr, block->data);
	TEST_ASSERT_EQUAL_INT(size, block->size);
	TEST_ASSERT_NULL(block->next);
	ft_free(ptr);
}

void free_all_sets_heap_null(void)
{
	char *block = (char *)ft_malloc(SMALL_ALLOC_SIZE + 1);
	ft_strncpy(block, "hello world", 12);
	TEST_ASSERT_NOT_NULL(block);
	ft_free(block);
	TEST_ASSERT_NULL(g_malloc.heap_large);
}

void can_allocate_100_times(void)
{
	void *blocks[100];
	for (int i = 0; i < 100; i++)
	{
		blocks[i] = ft_malloc(SMALL_ALLOC_SIZE + 1);
	}
	TEST_ASSERT_NOT_NULL(blocks[99]);
	for (int i = 0; i < 100; i++)
	{
		ft_free(blocks[i]);
	}
	TEST_ASSERT_NULL(g_malloc.heap_large);
}

void can_allocate_1000_times(void)
{
	void *blocks[1000];
	for (int i = 0; i < 1000; i++)
	{
		blocks[i] = ft_malloc(SMALL_ALLOC_SIZE + 1);
	}
	TEST_ASSERT_NOT_NULL(blocks[999]);
	for (int i = 0; i < 1000; i++)
	{
		ft_free(blocks[i]);
	}
	TEST_ASSERT_NULL(g_malloc.heap_large);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(single_allocation);
	RUN_TEST(verify_alloc_info);
	RUN_TEST(free_all_sets_heap_null);
	RUN_TEST(can_allocate_100_times);
	RUN_TEST(can_allocate_1000_times);
	return UNITY_END();
}
