/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_subject_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/05/13 14:17:46 by wkorande         ###   ########.fr       */
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

void test2(void)
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char *)malloc(1024);
		addr[0] = 42;
		free(addr);
		i++;
	}
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test2);
	return UNITY_END();
}
