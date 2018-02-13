/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:38:59 by mcanal            #+#    #+#             */
/*   Updated: 2018/02/13 19:33:10 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob tests
*/

#include "super_test_3000.h"
#include "glob.h"

struct s_test_glob {
	char *pattern;
	int flags;
	t_glob pglob;
	int expected;
};

static struct s_test_glob test_glob_arr[] = {
	{"*ab*cd*", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"*abcd*", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"*abcd*abcdef*", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"*a*b*[ef]*[cd]*g*", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"*a*b*[bc]*[ef]*g*", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"*ac*ae*ag*", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"*ac*", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"*bc", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"*b", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"?*?", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"??*", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"*??", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"?x?", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"??", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"?", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"[!]a-ceg-ik[]", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"[]a-ceg-ik[]", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"[a-c-e-g]", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"[a-c]", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"[!ab]", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"[ab]", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"[!a]", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"[a]", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
	{"a", 0, {0, NULL, 0, 0}, GLOB_SUCCESS},
};

static void glob_testux(char const *pat, int flags, t_glob *pglob, int expected)
{
	int ret = globctor(pat, flags, pglob);

	if (ret != expected) {
		MU_ASSERT(
			ret == expected,
			"glob return mismatch:\n    [pat='%s', flags='%d', test=%d, ctrl:%d, pglob={gl_pathc:%zu, *gl_pathv:'%s', gl_offs:%zu, gl_flags:%d}]",
			pat, flags, ret, expected,
			pglob->gl_pathc, *pglob->gl_pathv, pglob->gl_offs, pglob->gl_flags
		);
	}
}

void test_glob()
{
	for (unsigned int i = 0; i < sizeof(test_glob_arr) / sizeof(struct s_test_glob); i++) {
		glob_testux(
			test_glob_arr[i].pattern,
			test_glob_arr[i].flags,
			&test_glob_arr[i].pglob,
			test_glob_arr[i].expected
		);
	}

}
