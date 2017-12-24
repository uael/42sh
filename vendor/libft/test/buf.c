/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test/buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static int	test_ctor(void);

t_test		g_tests[] =
{
	{"ctor", test_ctor},
	{NULL, NULL}
};

int			setup(void)
{
	return (YEP);
}

int			teardown(void)
{
	return (YEP);
}

static int	test_ctor(void)
{
	return (YEP);
}
