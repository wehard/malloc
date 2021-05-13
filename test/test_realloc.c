/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_realloc.c                                     :+:      :+:    :+:   */
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

void realloc_tiny_shrink(void)
{
	void *tiny = malloc(TINY_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(tiny);
	void *shrunk = realloc(tiny, TINY_ALLOC_SIZE / 2);
	TEST_ASSERT_NOT_NULL(shrunk);
	free(tiny);
	free(shrunk);
}

void realloc_tiny_grow(void)
{
	void *tiny = malloc(32);
	TEST_ASSERT_NOT_NULL(tiny);
	void *grown = realloc(tiny, TINY_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(grown);
	free(tiny);
	free(grown);
}

void realloc_tiny_to_small_changes_zone(void)
{
	void *tiny = malloc(32);
	TEST_ASSERT_NOT_NULL(tiny);
	TEST_ASSERT_NULL(g_malloc.heap_small);
	void *grown = realloc(tiny, SMALL_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(grown);
	TEST_ASSERT_NULL(g_malloc.heap_tiny);
	TEST_ASSERT_NOT_NULL(g_malloc.heap_small);
	free(tiny);
	free(grown);
}

void realloc_tiny_to_large_changes_zone(void)
{
	void *tiny = malloc(32);
	TEST_ASSERT_NOT_NULL(tiny);
	TEST_ASSERT_NULL(g_malloc.heap_large);
	void *large = realloc(tiny, SMALL_ALLOC_SIZE + 128);
	TEST_ASSERT_NOT_NULL(large);
	TEST_ASSERT_NULL(g_malloc.heap_tiny);
	TEST_ASSERT_NOT_NULL(g_malloc.heap_large);
	free(tiny);
	free(large);
}

void realloc_small_to_tiny_does_not_change_zone(void)
{
	void *small = malloc(SMALL_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(small);
	TEST_ASSERT_NOT_NULL(g_malloc.heap_small);
	TEST_ASSERT_NULL(g_malloc.heap_tiny);
	void *tiny = realloc(small, TINY_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(tiny);
	TEST_ASSERT_NULL(g_malloc.heap_tiny);
	TEST_ASSERT_NOT_NULL(g_malloc.heap_small);
	free(small);
	free(tiny);
}

void realloc_small_to_large_changes_zone(void)
{
	void *small = malloc(SMALL_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(small);
	TEST_ASSERT_NULL(g_malloc.heap_large);
	void *large = realloc(small, SMALL_ALLOC_SIZE + 128);
	TEST_ASSERT_NOT_NULL(large);
	TEST_ASSERT_NULL(g_malloc.heap_small);
	TEST_ASSERT_NOT_NULL(g_malloc.heap_large);
	free(small);
	free(large);
}

void realloc_large_to_small_does_not_change_zone(void)
{
	void *large = malloc(SMALL_ALLOC_SIZE + 128);
	TEST_ASSERT_NOT_NULL(large);
	TEST_ASSERT_NOT_NULL(g_malloc.heap_large);
	TEST_ASSERT_NULL(g_malloc.heap_small);
	void *small = realloc(large, SMALL_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(small);
	TEST_ASSERT_NULL(g_malloc.heap_small);
	TEST_ASSERT_NOT_NULL(g_malloc.heap_large);
	free(small);
	free(large);
}

void realloc_large_to_tiny_does_not_change_zone(void)
{
	void *large = malloc(SMALL_ALLOC_SIZE + 128);
	TEST_ASSERT_NOT_NULL(large);
	TEST_ASSERT_NOT_NULL(g_malloc.heap_large);
	TEST_ASSERT_NULL(g_malloc.heap_tiny);
	void *tiny = realloc(large, TINY_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(tiny);
	TEST_ASSERT_NULL(g_malloc.heap_tiny);
	TEST_ASSERT_NOT_NULL(g_malloc.heap_large);
	free(tiny);
	free(large);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(realloc_tiny_shrink);
	RUN_TEST(realloc_tiny_grow);
	RUN_TEST(realloc_tiny_to_small_changes_zone);
	RUN_TEST(realloc_tiny_to_large_changes_zone);
	RUN_TEST(realloc_small_to_tiny_does_not_change_zone);
	RUN_TEST(realloc_small_to_large_changes_zone);
	RUN_TEST(realloc_large_to_small_does_not_change_zone);
	RUN_TEST(realloc_large_to_tiny_does_not_change_zone);
	return UNITY_END();
}
