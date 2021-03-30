/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_subject_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/03/30 14:26:05 by wkorande         ###   ########.fr       */
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

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test0);
	return UNITY_END();
}
