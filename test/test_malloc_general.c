/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc_general.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/02/28 19:59:10 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "malloc.h"
#include "libft.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void should_initialize_when_called_once(void)
{
	void *ptr = ft_malloc(TINY_ALLOC_SIZE);
	TEST_ASSERT_EQUAL_INT(g_malloc.initialized, 1);
	ft_free(ptr);
}

void should_reset_initialized_when_all_freed(void)
{
	void *ptr = ft_malloc(TINY_ALLOC_SIZE);
	TEST_ASSERT_EQUAL_INT(g_malloc.initialized, 1);
	ft_free(ptr);
	TEST_ASSERT_EQUAL_INT(g_malloc.initialized, 0);
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
	RUN_TEST(should_initialize_when_called_once);
	// RUN_TEST(should_reset_initialized_when_all_freed);
	RUN_TEST(allocate_and_free_resets_heaps);
	return UNITY_END();
}
