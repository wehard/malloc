/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/02/23 17:35:44 by wkorande         ###   ########.fr       */
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

void test_malloc_allocate_small(void)
{
	char *block = (char *)ft_malloc(SMALL_ALLOC_SIZE);
	ft_strncpy(block, "hello world", 12);
	TEST_ASSERT_NOT_NULL(block);
	TEST_ASSERT_EQUAL_CHAR('h', block[0]);
	TEST_ASSERT_EQUAL_CHAR('d', block[10]);
}

void test_malloc_free_small(void)
{
	char *block = (char *)ft_malloc(SMALL_ALLOC_SIZE);
	ft_strncpy(block, "hello world", 12);
	TEST_ASSERT_NOT_NULL(block);
	ft_free(block);
	TEST_ASSERT_NULL(g_malloc.small_blocks);
}

// not needed when using generate_test_runner.rb
int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_malloc_allocate_small);
	RUN_TEST(test_malloc_free_small);
	return UNITY_END();
}