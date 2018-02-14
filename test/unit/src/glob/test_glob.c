/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:38:59 by mcanal            #+#    #+#             */
/*   Updated: 2018/02/14 15:28:21 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob tests
*/

#include "super_test_3000.h"
#include "ft_glob.h"
#include <glob.h>

static glob_t ctrl_glob_struct;

struct s_test_glob {
	char *pattern;
	int flags;
	t_glob pglob;
};

static struct s_test_glob test_glob_arr[] = {
	{"*ab*cd*", 0, {0, NULL, 0, 0}},
	{"*abcd*", 0, {0, NULL, 0, 0}},
	{"*abcd*abcdef*", 0, {0, NULL, 0, 0}},
	{"*a*b*[ef]*[cd]*g*", 0, {0, NULL, 0, 0}},
	{"*a*b*[bc]*[ef]*g*", 0, {0, NULL, 0, 0}},
	{"*ac*ae*ag*", 0, {0, NULL, 0, 0}},
	{"*ac*", 0, {0, NULL, 0, 0}},
	{"*bc", 0, {0, NULL, 0, 0}},
	{"*b", 0, {0, NULL, 0, 0}},
	{"?*?", 0, {0, NULL, 0, 0}},
	{"??*", 0, {0, NULL, 0, 0}},
	{"*??", 0, {0, NULL, 0, 0}},
	{"?x?", 0, {0, NULL, 0, 0}},
	{"??", 0, {0, NULL, 0, 0}},
	{"?", 0, {0, NULL, 0, 0}},
	{"[!]a-ceg-ik[]", 0, {0, NULL, 0, 0}},
	{"[]a-ceg-ik[]", 0, {0, NULL, 0, 0}},
	{"[a-c-e-g]", 0, {0, NULL, 0, 0}},
	{"[a-c]", 0, {0, NULL, 0, 0}},
	{"[!ab]", 0, {0, NULL, 0, 0}},
	{"[ab]", 0, {0, NULL, 0, 0}},
	{"[!a]", 0, {0, NULL, 0, 0}},
	{"[a]", 0, {0, NULL, 0, 0}},
	{"", 0, {0, NULL, 0, 0}},
	{"a", 0, {0, NULL, 0, 0}},
};


static void glob_testux(char const *pat, int flags, t_glob *pglob)
{
	int expected = glob(pat, flags, NULL, &ctrl_glob_struct);
	int ret = globctor(pat, flags, pglob);

	if (ret != expected) {
		MU_ASSERT(
			ret == expected,
			"glob return mismatch:\n    [pat='%s', flags='%d', test=%d, ctrl:%d, pglob={gl_pathc:%zu, gl_pathv:%zu, gl_offs:%zu, gl_flags:%d}]",
			pat, flags, ret, expected,
			pglob->gl_pathc, pglob->gl_pathv, pglob->gl_offs, pglob->gl_flags
		);
	}

	//TODO: compare pglob->{ac,__av__,offs,flags}
}

void test_glob()
{
	for (unsigned int i = 0; i < sizeof(test_glob_arr) / sizeof(struct s_test_glob); i++) {
		ctrl_glob_struct.gl_pathc = test_glob_arr[i].pglob.gl_pathc;
		ctrl_glob_struct.gl_pathv = test_glob_arr[i].pglob.gl_pathv; //TODO
		ctrl_glob_struct.gl_offs = test_glob_arr[i].pglob.gl_offs;
		ctrl_glob_struct.gl_flags = test_glob_arr[i].pglob.gl_flags;

		glob_testux(
			test_glob_arr[i].pattern,
			test_glob_arr[i].flags,
			&(test_glob_arr[i].pglob)
		);
	}

}
