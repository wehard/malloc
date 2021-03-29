/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc_general.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/29 16:17:40 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "malloc.h"
#include "malloc_internal.h"
#include "libft.h"
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
	void *ptr = ft_malloc(TINY_ALLOC_SIZE);
	TEST_ASSERT_EQUAL_INT(1, ptr_is_valid(ptr));
	ft_free(ptr);
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
	TEST_ASSERT_NULL(g_malloc.tiny_blocks);
	TEST_ASSERT_NULL(g_malloc.small_blocks);
	TEST_ASSERT_NULL(g_malloc.large_blocks);
	TEST_ASSERT_EQUAL_INT(getpagesize(), g_malloc.page_size);
}

void should_initialize_when_called_once(void)
{
	void *ptr = ft_malloc(TINY_ALLOC_SIZE);
	TEST_ASSERT_EQUAL_INT(1, g_malloc.initialized);
	ft_free(ptr);
}

void should_reset_initialized_when_all_freed(void)
{
	void *ptr = ft_malloc(TINY_ALLOC_SIZE);
	TEST_ASSERT_EQUAL_INT(1, g_malloc.initialized);
	ft_free(ptr);
	TEST_ASSERT_EQUAL_INT(0, g_malloc.initialized);
}

void allocate_and_free_resets_heaps(void)
{
	void *tiny = ft_malloc(TINY_ALLOC_SIZE);
	void *small = ft_malloc(SMALL_ALLOC_SIZE);
	void *large = ft_malloc(SMALL_ALLOC_SIZE + 128);
	ft_free(tiny);
	ft_free(small);
	ft_free(large);
	TEST_ASSERT_NULL(g_malloc.tiny_blocks);
	TEST_ASSERT_NULL(g_malloc.small_blocks);
	TEST_ASSERT_NULL(g_malloc.large_blocks);
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
