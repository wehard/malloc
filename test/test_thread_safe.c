/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_thread_safe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/01 17:26:43 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "malloc.h"
#include "libft.h"

const int num_threads = 10;
uint64_t ptrs[num_threads];

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
	void *ptr = ft_malloc(TINY_ALLOC_SIZE);

	int ret = pthread_mutex_lock(&g_malloc_mutex);
	TEST_ASSERT_EQUAL_INT(0, ret);
	pthread_mutex_unlock(&g_malloc_mutex);
	ft_free(ptr);
}

static void *malloc_thread(void *ptr)
{
	void *p = ft_malloc(TINY_ALLOC_SIZE);
	*(uint64_t*)ptr = (uint64_t)&p;
	return NULL;
}

void should_allocate_when_call_from_thread(void)
{
	pthread_t threads[num_threads];

	int i = 0;
	while (i < num_threads)
	{
		pthread_create(&threads[i], NULL, malloc_thread, &ptrs[i]);
		i++;
	}

	i = 0;
	while (i < num_threads)
	{
		pthread_join(threads[i], NULL);
		i++;
	}

	i = 0;
	while (i < num_threads)
	{
		printf("%d %#zx ptr %p\n", i, ptrs[i], (void*)ptrs[i]);
		// TEST_ASSERT_EQUAL_INT(TRUE, ptr_is_valid((void*)ptrs[i]));
		void *p = (void*)ptrs[i];
		if(!ptr_is_valid(p))
			printf("Invalid pointer %p!\n", p);
		i++;
	}
}

int main(void)
{
	UNITY_BEGIN();
	// RUN_TEST(should_init_mutex);
	RUN_TEST(should_allocate_when_call_from_thread);
	return UNITY_END();
}
