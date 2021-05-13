/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_subject_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/05/13 14:19:05 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "malloc.h"
#include "malloc_internal.h"
#include <unistd.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test4(void)
{
	char *addr;

	addr = (char *)malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		ft_putstr_fd("Bonjours\n", 1);
	else
		TEST_FAIL();
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test4);
	return UNITY_END();
}
