/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/05/13 14:18:11 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "malloc.h"
#include "malloc_internal.h"

void	setUp(void)
{
}

void	tearDown(void)
{
}

void	free_null_does_not_fail(void)
{
	void	*ptr;

	ptr = NULL;
	free(ptr);
}

void	free_garbage_ptr_does_not_fail(void)
{
	int	*ptr;

	*ptr = 0xDEADBEEF;
	free(ptr);
}

void	realloc_tiny(void)
{
	void	*tiny;

	tiny = malloc(TINY_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(tiny);
	free(tiny);
}

void	free_small(void)
{
	void	*small;

	small = malloc(SMALL_ALLOC_SIZE);
	TEST_ASSERT_NOT_NULL(small);
	free(small);
}

void	free_large(void)
{
	void	*large;

	large = malloc(SMALL_ALLOC_SIZE + 1);
	TEST_ASSERT_NOT_NULL(large);
	free(large);
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(free_null_does_not_fail);
	RUN_TEST(realloc_tiny);
	RUN_TEST(free_small);
	RUN_TEST(free_large);
	RUN_TEST(free_garbage_ptr_does_not_fail);
	return (UNITY_END());
}
