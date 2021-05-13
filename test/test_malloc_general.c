/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc_general.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/05/13 14:22:54 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "malloc.h"
#include "malloc_internal.h"
#include <unistd.h>

void init_malloc(void);
int ptr_is_valid(void *ptr);

void setUp(void)
{
}

void tearDown(void)
{
}

void should_get_valid_pointer(void)
{
	void *ptr = malloc(TINY_ALLOC_SIZE);
	TEST_ASSERT_EQUAL_INT(1, ptr_is_valid(ptr));
	free(ptr);
}

void should_get_invalid_pointer_when_pointer_not_allocated(void)
{
	int a = 1234;
	void *ptr = &a;
	TEST_ASSERT_FALSE(ptr_is_valid(ptr));
}

void should_init_successfully(void)
{
	init_malloc();
	TEST_ASSERT_EQUAL_INT(1, g_malloc.initialized);
	TEST_ASSERT_NULL(g_malloc.heap_tiny);
	TEST_ASSERT_NULL(g_malloc.heap_small);
	TEST_ASSERT_NULL(g_malloc.heap_large);
	TEST_ASSERT_EQUAL_INT(getpagesize(), g_malloc.page_size);
}

void should_initialize_when_called_once(void)
{
	void *ptr = malloc(TINY_ALLOC_SIZE);
	TEST_ASSERT_EQUAL_INT(1, g_malloc.initialized);
	free(ptr);
}

void should_reset_initialized_when_all_freed(void)
{
	void *ptr = malloc(TINY_ALLOC_SIZE);
	TEST_ASSERT_EQUAL_INT(1, g_malloc.initialized);
	free(ptr);
	TEST_ASSERT_EQUAL_INT(0, g_malloc.initialized);
}

void allocate_and_free_resets_heaps(void)
{
	void *tiny = malloc(TINY_ALLOC_SIZE);
	void *small = malloc(SMALL_ALLOC_SIZE);
	void *large = malloc(SMALL_ALLOC_SIZE + 128);
	free(tiny);
	free(small);
	free(large);
	TEST_ASSERT_NULL(g_malloc.heap_tiny);
	TEST_ASSERT_NULL(g_malloc.heap_small);
	TEST_ASSERT_NULL(g_malloc.heap_large);
}



int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(should_get_valid_pointer);
	RUN_TEST(should_get_invalid_pointer_when_pointer_not_allocated);
	RUN_TEST(should_init_successfully);
	RUN_TEST(should_initialize_when_called_once);
	// RUN_TEST(should_reset_initialized_when_all_freed);
	RUN_TEST(allocate_and_free_resets_heaps);
	return UNITY_END();
}
