/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_thread_safe.c                                 :+:      :+:    :+:   */
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

const int num_threads = 10;
void *ptrs[num_threads];

int ptr_is_valid(void *ptr);

void setUp(void)
{
	int i = 0;
	while (i < num_threads)
	{
		ptrs[i] = 0;
		i++;
	}
}

void tearDown(void)
{
}

void should_init_mutex(void)
{
	void *ptr = malloc(TINY_ALLOC_SIZE);

	int ret = pthread_mutex_lock(&g_malloc_mutex);
	TEST_ASSERT_EQUAL_INT(0, ret);
	pthread_mutex_unlock(&g_malloc_mutex);
	free(ptr);
}

static void *malloc_thread(void *arg)
{
	arg = 0;
	void *p = malloc(TINY_ALLOC_SIZE);
	return p;
}

void should_allocate_when_call_from_thread(void)
{
	pthread_t threads[num_threads];

	int i = 0;
	while (i < num_threads)
	{
		pthread_create(&threads[i], NULL, malloc_thread, NULL);
		pthread_join(threads[i], &ptrs[i]);
		i++;
	}

	i = 0;
	while (i < num_threads)
	{
		
		i++;
	}

	i = 0;
	while (i < num_threads)
	{
		TEST_ASSERT_EQUAL_INT(TRUE, ptr_is_valid(ptrs[i]));
		free(ptrs[i]);
		i++;
	}
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(should_init_mutex);
	RUN_TEST(should_allocate_when_call_from_thread);
	return UNITY_END();
}
