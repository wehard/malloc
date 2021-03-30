/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_subject_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/30 14:26:37 by wkorande         ###   ########.fr       */
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

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test1);
	return UNITY_END();
}
