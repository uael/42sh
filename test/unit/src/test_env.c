/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:38:59 by mcanal            #+#    #+#             */
/*   Updated: 2018/02/09 10:59:02 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** just a dummy test to check if minuit is working as expect
*/

#include "super_test_3000.h"

void test_env()
{
	extern char **environ;
	char *test;

	sh_envinit(environ);
	sh_setenv("foo", "bar");
	MU_ASSERT(
		(test = sh_getenv("foo")) != 0,
		"getenv failed (return)"
	);
	MU_ASSERT(
		!ft_strcmp(test, "bar"),
		"getenv failed (test:%s, ctrl:bar)", test
	);
}
