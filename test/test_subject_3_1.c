/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_subject_3_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/05/13 14:22:46 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "malloc.h"
#include "malloc_internal.h"
#include <unistd.h>
#include <string.h>

#define M (1024*1024)

void setUp(void)
{
}

void tearDown(void)
{
}

void test3_1(void)
{
	char *addr1;
	char *addr2;
	char *addr3;

	addr1 = (char *)malloc(16 * M);
	strcpy(addr1, "Bonjours\n");
	TEST_ASSERT_EQUAL_STRING(addr1, "Bonjours\n");
	addr2 = (char *)malloc(16 * M);
	addr3 = (char *)realloc(addr1, 128 * M);
	addr3[127 * M] = 42;
	TEST_ASSERT_EQUAL_STRING(addr3, "Bonjours\n");
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test3_1);
	return UNITY_END();
}
