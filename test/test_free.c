/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/29 16:16:40 by wkorande         ###   ########.fr       */
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

void free_null_does_not_fail(void)
{
	void *ptr = NULL;
	ft_free(ptr);
}

void free_garbage_ptr_does_not_fail(void)
{
	int ptr = 0xDEADBEEF;
	ft_free(&ptr);
}

void realloc_tiny(void)
{
	void *tiny = ft_malloc(TINY_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(tiny);
	ft_free(tiny);
	// TEST_ASSERT_NULL(tiny);
}

void free_small(void)
{
	void *small = ft_malloc(SMALL_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(small);
	ft_free(small);
	// TEST_ASSERT_NULL(small);
}

void free_large(void)
{
	void *large = ft_malloc(SMALL_ALLOC_SIZE + 1);
	TEST_ASSERT_NOT_NULL(large);
	ft_free(large);
	// TEST_ASSERT_NULL(large);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(free_null_does_not_fail);
	RUN_TEST(realloc_tiny);
	RUN_TEST(free_small);
	RUN_TEST(free_large);
	RUN_TEST(free_garbage_ptr_does_not_fail);
	return UNITY_END();
}
