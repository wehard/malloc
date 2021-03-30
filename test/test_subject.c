/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_subject.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/30 11:41:00 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "malloc.h"
#include "malloc_internal.h"
#include "libft.h"
#include <unistd.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test0(void)
{
	int i;

	i = 0;
	while (i < 1024)
	{
		i++;
	}
}

void test1(void)
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char *)ft_malloc(1024);
		addr[0] = 42;
		i++;
	}
}

void test2(void)
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char *)ft_malloc(1024);
		addr[0] = 42;
		ft_free(addr);
		i++;
	}
}

#define M (1024*1024)

void print(char *s)
{
	write(1, s, strlen(s));
}

void test3(void)
{
	char *addr1;
	char *addr3;

	addr1 = (char *)ft_malloc(16*M);
	strcpy(addr1, "Bonjours\n");
	// print(addr1);
	TEST_ASSERT_EQUAL_STRING(addr1, "Bonjours\n");
	addr3 = (char *)ft_realloc(addr1, 128 * M);
	addr3[127 * M] = 42;
	// print(addr3);
	TEST_ASSERT_EQUAL_STRING(addr3, "Bonjours\n");
}

void test3_1(void)
{
	char *addr1;
	char *addr2;
	char *addr3;

	addr1 = (char *)ft_malloc(16 * M);
	strcpy(addr1, "Bonjours\n");
	// print(addr1);
	TEST_ASSERT_EQUAL_STRING(addr1, "Bonjours\n");
	addr2 = (char *)ft_malloc(16 * M);
	addr3 = (char *)ft_realloc(addr1, 128 * M);
	addr3[127 * M] = 42;
	// print(addr3);
	TEST_ASSERT_EQUAL_STRING(addr3, "Bonjours\n");
}

void test4(void)
{
	char *addr;

	addr = (char *)ft_malloc(16);
	ft_free(NULL);
	ft_free((void *)addr + 5);
	if (ft_realloc((void *)addr + 5, 10) == NULL)
	{
		// print("Bonjours\n");
		TEST_FAIL_MESSAGE("Bonjours");
	}
}

void test5(void)
{
	ft_malloc(1024);
	ft_malloc(1024 * 32);
	ft_malloc(1024 * 1024);
	ft_malloc(1024 * 1024 * 16);
	ft_malloc(1024 * 1024 * 128);
	show_alloc_mem();
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test0);
	RUN_TEST(test1);
	RUN_TEST(test2);
	RUN_TEST(test3);
	RUN_TEST(test3_1);
	RUN_TEST(test4);
	RUN_TEST(test5);
	return UNITY_END();
}
