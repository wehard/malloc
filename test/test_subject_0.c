/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_subject_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:43:01 by wkorande          #+#    #+#             */
/*   Updated: 2021/05/13 14:20:03 by wkorande         ###   ########.fr       */
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
