/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc_small.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/29 16:16:48 by wkorande         ###   ########.fr       */
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
	char *block = (char *)ft_malloc(SMALL_ALLOC_SIZE);
	ft_strncpy(block, "hello world", 12);
	TEST_ASSERT_NOT_NULL(block);
	TEST_ASSERT_EQUAL_CHAR('h', block[0]);
	TEST_ASSERT_EQUAL_CHAR('d', block[10]);
}

void verify_alloc_info(void)
{
	void *ptr = ft_malloc(SMALL_ALLOC_SIZE);
	t_block *block = ptr - sizeof(t_block);

	TEST_ASSERT_NOT_NULL(ptr);
	TEST_ASSERT_NOT_NULL(block);
	TEST_ASSERT_EQUAL_PTR(ptr, block->data);
	TEST_ASSERT_EQUAL_INT(SMALL_ALLOC_SIZE, block->size);
}

void free_all_sets_heap_null(void)
{
	char *block = (char *)ft_malloc(SMALL_ALLOC_SIZE);
	ft_strncpy(block, "hello world", 12);
	TEST_ASSERT_NOT_NULL(block);
	ft_free(block);
	TEST_ASSERT_NULL(g_malloc.small_blocks);
}

void tiny_allocation_does_not_affect_small_heap(void)
{
	char *block = (char*)ft_malloc(TINY_ALLOC_SIZE);
	ft_free(block);
	TEST_ASSERT_NULL(g_malloc.small_blocks);
}

void can_allocate_100_times(void)
{
	void *blocks[100];
	for (int i = 0; i < 100; i++)
	{
		blocks[i] = ft_malloc(SMALL_ALLOC_SIZE);
	}
	TEST_ASSERT_NOT_NULL(blocks[99]);
	for (int i = 0; i < 100; i++)
	{
		ft_free(blocks[i]);
	}
	TEST_ASSERT_NULL(g_malloc.small_blocks);
}

void cannot_allocate_1000_times(void)
{
	void *blocks[1000];
	for (int i = 0; i < 1000; i++)
	{
		blocks[i] = ft_malloc(SMALL_ALLOC_SIZE);
	}
	TEST_ASSERT_NULL(blocks[999]);
	for (int i = 0; i < 1000; i++)
	{
		ft_free(blocks[i]);
	}
	TEST_ASSERT_NULL(g_malloc.tiny_blocks);
}

// not needed when using generate_test_runner.rb
int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(single_allocation);
	RUN_TEST(verify_alloc_info);
	RUN_TEST(free_all_sets_heap_null);
	RUN_TEST(tiny_allocation_does_not_affect_small_heap);
	RUN_TEST(can_allocate_100_times);
	RUN_TEST(cannot_allocate_1000_times);
	return UNITY_END();
}
