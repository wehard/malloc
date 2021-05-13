/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc_small.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/05/13 13:23:09 by wkorande         ###   ########.fr       */
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
	char *block = (char *)malloc(SMALL_ALLOC_SIZE);
	ft_strncpy(block, "hello world", 12);
	TEST_ASSERT_NOT_NULL(block);
	TEST_ASSERT_EQUAL_CHAR('h', block[0]);
	TEST_ASSERT_EQUAL_CHAR('d', block[10]);
}

void verify_alloc_info(void)
{
	void *ptr = malloc(SMALL_ALLOC_SIZE);
	t_block *block = ptr - sizeof(t_block);

	TEST_ASSERT_NOT_NULL(ptr);
	TEST_ASSERT_NOT_NULL(block);
	TEST_ASSERT_EQUAL_PTR(ptr, block->data);
	TEST_ASSERT_EQUAL_INT(SMALL_ALLOC_SIZE, block->size);
}

void free_all_sets_heap_null(void)
{
	char *block = (char *)malloc(SMALL_ALLOC_SIZE);
	ft_strncpy(block, "hello world", 12);
	TEST_ASSERT_NOT_NULL(block);
	free(block);
	TEST_ASSERT_NULL(g_malloc.heap_small);
}

void tiny_allocation_does_not_affect_small_heap(void)
{
	char *block = (char*)malloc(TINY_ALLOC_SIZE);
	free(block);
	TEST_ASSERT_NULL(g_malloc.heap_small);
}

void can_allocate_100_times(void)
{
	void *blocks[100];
	for (int i = 0; i < 100; i++)
	{
		blocks[i] = malloc(SMALL_ALLOC_SIZE);
	}
	TEST_ASSERT_NOT_NULL(blocks[99]);
	for (int i = 0; i < 100; i++)
	{
		free(blocks[i]);
	}
	TEST_ASSERT_NULL(g_malloc.heap_small);
}

void can_allocate_1024_times(void)
{
	void *blocks[1024];
	for (int i = 0; i < 1024; i++)
	{
		blocks[i] = malloc(SMALL_ALLOC_SIZE);
	}
	TEST_ASSERT_NOT_NULL(blocks[1023]);
	for (int i = 0; i < 1024; i++)
	{
		free(blocks[i]);
	}
	TEST_ASSERT_NULL(g_malloc.heap_tiny);
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
	RUN_TEST(can_allocate_1024_times);
	return UNITY_END();
}
