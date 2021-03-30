/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_subject_3_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/30 14:54:13 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "malloc.h"
#include "malloc_internal.h"
#include "libft.h"
#include <unistd.h>

#define M (1024*1024)

void setUp(void)
{
}

void tearDown(void)
{
}

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
	print(addr1);
	TEST_ASSERT_EQUAL_STRING(addr1, "Bonjours\n");
	addr3 = (char *)ft_realloc(addr1, 128 * M);
	// addr3[127 * M] = 42;
	print(addr3);
	TEST_ASSERT_EQUAL_STRING(addr3, "Bonjours\n");
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test3);
	return UNITY_END();
}
