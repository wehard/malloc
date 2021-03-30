/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_subject_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/30 14:27:15 by wkorande         ###   ########.fr       */
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

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test2);
	return UNITY_END();
}
