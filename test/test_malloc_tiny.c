/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc_tiny.c                                 :+:      :+:    :+:   */
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

void simple_allocation(void)
{
	char *block = (char*)malloc(12);
	ft_strncpy(block, "hello world", 12);
	TEST_ASSERT_NOT_NULL(block);
	TEST_ASSERT_EQUAL_CHAR('h', block[0]);
	TEST_ASSERT_EQUAL_CHAR('d', block[10]);
	free(block);
}

void verify_alloc_info(void)
{
	void *ptr = malloc(TINY_ALLOC_SIZE);
	t_block *block = ptr - sizeof(t_block);

	TEST_ASSERT_NOT_NULL(ptr);
	TEST_ASSERT_NOT_NULL(block);
	TEST_ASSERT_EQUAL_PTR(ptr, block->data);
	TEST_ASSERT_EQUAL_INT(TINY_ALLOC_SIZE, block->size);
}

void free_all_sets_heap_null(void)
{
	char *block = (char*)malloc(12);
	ft_strncpy(block, "hello world", 12);
	TEST_ASSERT_NOT_NULL(block);
	free(block);
	TEST_ASSERT_NULL(g_malloc.heap_tiny);
}

void small_allocation_not_affect_tiny_zone(void)
{
	char *block = (char*)malloc(TINY_ALLOC_SIZE + 1);
	free(block);
	TEST_ASSERT_NULL(g_malloc.heap_small);
	TEST_ASSERT_NULL(g_malloc.heap_tiny);
}

void can_allocate_100_times(void)
{
	void *blocks[100];
	for (int i = 0; i < 100; i++)
	{
		blocks[i] = malloc(TINY_ALLOC_SIZE);
	}
	TEST_ASSERT_NOT_NULL(blocks[99]);
	for (int i = 0; i < 100; i++)
	{
		free(blocks[i]);
	}
	TEST_ASSERT_NULL(g_malloc.heap_tiny);
}

void cannot_allocate_1000_times(void)
{
	void *blocks[1000];
	for (int i = 0; i < 1000; i++)
	{
		blocks[i] = malloc(TINY_ALLOC_SIZE);
	}
	TEST_ASSERT_NULL(blocks[999]);
	for (int i = 0; i < 1000; i++)
	{
		free(blocks[i]);
	}
	TEST_ASSERT_NULL(g_malloc.heap_tiny);
}

// not needed when using generate_test_runner.rb
int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(simple_allocation);
	RUN_TEST(verify_alloc_info);
	RUN_TEST(free_all_sets_heap_null);
	RUN_TEST(small_allocation_not_affect_tiny_zone);
	RUN_TEST(can_allocate_100_times);
	RUN_TEST(cannot_allocate_1000_times);
	return UNITY_END();
}
