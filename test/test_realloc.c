/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/02/25 18:18:05 by wkorande         ###   ########.fr       */
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

void realloc_tiny_shrink(void)
{
	void *tiny = ft_malloc(TINY_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(tiny);
	void *shrunk = ft_realloc(tiny, TINY_ALLOC_SIZE / 2);
	TEST_ASSERT_NOT_NULL(shrunk);
	ft_free(tiny);
	ft_free(shrunk);
}

void realloc_tiny_grow(void)
{
	void *tiny = ft_malloc(32);
	TEST_ASSERT_NOT_NULL(tiny);
	void *grown = ft_realloc(tiny, TINY_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(grown);
	ft_free(tiny);
	ft_free(grown);
}

void realloc_tiny_to_small_changes_zone(void)
{
	void *tiny = ft_malloc(32);
	TEST_ASSERT_NOT_NULL(tiny);
	TEST_ASSERT_NULL(g_malloc.small_blocks);
	void *grown = ft_realloc(tiny, SMALL_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(grown);
	TEST_ASSERT_NULL(g_malloc.tiny_blocks);
	TEST_ASSERT_NOT_NULL(g_malloc.small_blocks);
	ft_free(tiny);
	ft_free(grown);
}

void realloc_tiny_to_large_changes_zone(void)
{
	void *tiny = ft_malloc(32);
	TEST_ASSERT_NOT_NULL(tiny);
	TEST_ASSERT_NULL(g_malloc.large_blocks);
	void *large = ft_realloc(tiny, SMALL_ALLOC_SIZE + 128);
	TEST_ASSERT_NOT_NULL(large);
	TEST_ASSERT_NULL(g_malloc.tiny_blocks);
	TEST_ASSERT_NOT_NULL(g_malloc.large_blocks);
	ft_free(tiny);
	ft_free(large);
}

void realloc_small_to_tiny_changes_zone(void)
{
	void *small = ft_malloc(SMALL_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(small);
	TEST_ASSERT_NULL(g_malloc.tiny_blocks);
	void *tiny = ft_realloc(small, TINY_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(tiny);
	TEST_ASSERT_NULL(g_malloc.small_blocks);
	TEST_ASSERT_NOT_NULL(g_malloc.tiny_blocks);
	ft_free(small);
	ft_free(tiny);
}

void realloc_small_to_large_changes_zone(void)
{
	void *small = ft_malloc(SMALL_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(small);
	TEST_ASSERT_NULL(g_malloc.large_blocks);
	void *large = ft_realloc(small, SMALL_ALLOC_SIZE + 128);
	TEST_ASSERT_NOT_NULL(large);
	TEST_ASSERT_NULL(g_malloc.small_blocks);
	TEST_ASSERT_NOT_NULL(g_malloc.large_blocks);
	ft_free(small);
	ft_free(large);
}

void realloc_large_to_small_changes_zone(void)
{
	void *large = ft_malloc(SMALL_ALLOC_SIZE + 128);
	TEST_ASSERT_NOT_NULL(large);
	TEST_ASSERT_NOT_NULL(g_malloc.large_blocks);
	TEST_ASSERT_NULL(g_malloc.small_blocks);
	void *small = ft_realloc(large, SMALL_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(small);
	TEST_ASSERT_NULL(g_malloc.large_blocks);
	TEST_ASSERT_NOT_NULL(g_malloc.small_blocks);
	ft_free(small);
	ft_free(large);
}

void realloc_large_to_tiny_changes_zone(void)
{
	void *large = ft_malloc(SMALL_ALLOC_SIZE + 128);
	TEST_ASSERT_NOT_NULL(large);
	TEST_ASSERT_NOT_NULL(g_malloc.large_blocks);
	TEST_ASSERT_NULL(g_malloc.tiny_blocks);
	void *tiny = ft_realloc(large, TINY_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(tiny);
	TEST_ASSERT_NULL(g_malloc.large_blocks);
	TEST_ASSERT_NOT_NULL(g_malloc.tiny_blocks);
	ft_free(tiny);
	ft_free(large);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(realloc_tiny_shrink);
	RUN_TEST(realloc_tiny_grow);
	RUN_TEST(realloc_tiny_to_small_changes_zone);
	RUN_TEST(realloc_tiny_to_large_changes_zone);
	RUN_TEST(realloc_small_to_tiny_changes_zone);
	RUN_TEST(realloc_small_to_large_changes_zone);
	RUN_TEST(realloc_large_to_small_changes_zone);
	RUN_TEST(realloc_large_to_tiny_changes_zone);
	return UNITY_END();
}
