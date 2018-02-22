/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:38:59 by mcanal            #+#    #+#             */
/*   Updated: 2018/02/23 00:25:21 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob tests
*/

#include "super_test_3000.h"
#include "ft_glob.h"
#include <glob.h>

struct s_test_glob {
	char *pattern;
	int flags;
	t_glob pglob;
};

static char *glob_ret_strings[] = {
	"GLOB_SUCCESS",
	"GLOB_NOSPACE",
	"GLOB_ABORTED",
	"GLOB_NOMATCH",
	"GLOB_NOSYS",
	"GLOBUX_BOOM_BABY",
};

static char *glob_flags_strings[] = {
	"GLOB_ERR",
	"GLOB_MARK",
	"GLOB_NOSORT",
	"GLOB_DOOFFS",
	"GLOB_NOCHECK",
	"GLOB_APPEND",
	"GLOB_NOESCAPE",
	"GLOB_PERIOD",
	"GLOB_MAGCHAR",
	"GLOB_ALTDIRFUNC",
	"GLOB_BRACE",
	"GLOB_NOMAGIC",
	"GLOB_TILDE",
	"GLOB_ONLYDIR",
	"GLOB_TILDE_CHECK",
	"GLOB_CUSTOM",
};

#define FAT (1 << 24) //yolo
#define BIG (1 << 20) //yolo
#define SMALL (1 << 8) //yolo

static char print_buffer[FAT] = {0};
static char argv_input_buffer[BIG] = {0};
static char argv_test_buffer[BIG] = {0};
static char argv_ctrl_buffer[BIG] = {0};
static char flags_buffer[SMALL] = {0};
static char flags_input_buffer[SMALL] = {0};
static char flags_test_buffer[SMALL] = {0};
static char flags_ctrl_buffer[SMALL] = {0};

static glob_t ctrl_glob_struct;

#define TEST_FLAGS (GLOB_NOCHECK)

static struct s_test_glob test_glob_arr[] = {

	{"*ab*cd*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"*abcd*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"*abcd*abcdef*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"*a*b*[ef]*[cd]*g*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"*a*b*[bc]*[ef]*g*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"*ac*ae*ag*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"*ac*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"*bc", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"*b", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"?*?", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"??*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"*??", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"?x?", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"??", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"?", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[!]a-ceg-ik[]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[]a-ceg-ik[]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[a-c-e-g]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[a-c]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[!ab]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[ab]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[!a]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[a]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"a", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{".", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{".*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"*.*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"*", TEST_FLAGS, {0, NULL, 0, 0, 0}},

	{"/*ab*cd*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/*abcd*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/*abcd*abcdef*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/*a*b*[ef]*[cd]*g*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/*a*b*[bc]*[ef]*g*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/*ac*ae*ag*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/*ac*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/*bc", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/*b", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/?*?", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/??*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/*??", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/?x?", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/??", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/?", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/[!]a-ceg-ik[]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/[]a-ceg-ik[]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/[a-c-e-g]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/[a-c]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/[!ab]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/[ab]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/[!a]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/[a]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/a", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/.", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/.*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/*.*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/*", TEST_FLAGS, {0, NULL, 0, 0, 0}},

	{"/usr/lib/*ab*cd*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/*abcd*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/*abcd*abcdef*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/*a*b*[ef]*[cd]*g*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/*a*b*[bc]*[ef]*g*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/*ac*ae*ag*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/*ac*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/*bc", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/*b", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/?*?", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/??*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/*??", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/?x?", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/??", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/?", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/[!]a-ceg-ik[]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/[]a-ceg-ik[]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/[a-c-e-g]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/[a-c]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/[!ab]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/[ab]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/[!a]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/[a]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/a", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/.", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/.*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/*.*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/usr/lib/*", TEST_FLAGS, {0, NULL, 0, 0, 0}},

	{"./", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"*/", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"././././*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"././.././*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"../*/../*", TEST_FLAGS, {0, NULL, 0, 0, 0}},

	{"/usr/lib/", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"//usr//lib//*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"//usr///lib/////*", TEST_FLAGS, {0, NULL, 0, 0, 0}},

	{"\\[abc]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[abc\\]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"\\[abc\\]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[abc\\]def]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[abc\\\\\\]def]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[abc\\\\\\\\\\]def]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[abc\\\\\\\\\\\\\\]def]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[!a-y][42]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[^a-y][42]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[!a-z]", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"[^a-z]", TEST_FLAGS, {0, NULL, 0, 0, 0}},

	{"*/*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"*/*/*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/*/*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	/* {"/\*\/\*\/\*", TEST_FLAGS, {0, NULL, 0, 0, 0}}, */
	/* {"/usr/lib/\*\/\*\/\*", TEST_FLAGS, {0, NULL, 0, 0, 0}}, */

	{"????*/??*", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"/did/you/think/about/it", TEST_FLAGS, {0, NULL, 0, 0, 0}},
	{"good", TEST_FLAGS, {0, NULL, 0, 0, 0}},

	/* {"/and/this/", TEST_FLAGS, {0, NULL, 0, 0, 0}}, */
	/* {"///", TEST_FLAGS, {0, NULL, 0, 0, 0}}, */
	/* {".//////", TEST_FLAGS, {0, NULL, 0, 0, 0}}, */
	/* {"//usr//lib//", TEST_FLAGS, {0, NULL, 0, 0, 0}}, */
	/* {"//usr///lib/////", TEST_FLAGS, {0, NULL, 0, 0, 0}}, */
	/* {"//usr///lib/////\*\/", TEST_FLAGS, {0, NULL, 0, 0, 0}}, */
	/* {"//usr///lib/////\*\////", TEST_FLAGS, {0, NULL, 0, 0, 0}}, */

	/* {"~", TEST_FLAGS | GLOBUX_TILDE, {0, NULL, 0, 0, 0}}, */
	/* {"~/..", TEST_FLAGS | GLOBUX_TILDE, {0, NULL, 0, 0, 0}}, */
	/* {"~/\*", TEST_FLAGS | GLOBUX_TILDE, {0, NULL, 0, 0, 0}}, */
	/* {"~/\*\/???", TEST_FLAGS | GLOBUX_TILDE, {0, NULL, 0, 0, 0}}, */
	/* {"/~/..", TEST_FLAGS | GLOBUX_TILDE, {0, NULL, 0, 0, 0}}, */
	/* {"~/.emacs.d/\*\/\*~", TEST_FLAGS | GLOBUX_TILDE, {0, NULL, 0, 0, 0}}, */

	/* {"{src}", TEST_FLAGS | GLOBUX_BRACE, {0, NULL, 0, 0, 0}}, */
	/* {"{src,obj}", TEST_FLAGS | GLOBUX_BRACE, {0, NULL, 0, 0, 0}}, */
	/* {"{src,obj,include}", TEST_FLAGS | GLOBUX_BRACE, {0, NULL, 0, 0, 0}}, */
	/* {"./{,obj,include}", TEST_FLAGS | GLOBUX_BRACE, {0, NULL, 0, 0, 0}}, */
	/* {"./{src}/\*", TEST_FLAGS | GLOBUX_BRACE, {0, NULL, 0, 0, 0}}, */
	/* {"./{src,obj}/\*", TEST_FLAGS | GLOBUX_BRACE, {0, NULL, 0, 0, 0}}, */
	/* {"./{src,obj,include}/\*", TEST_FLAGS | GLOBUX_BRACE, {0, NULL, 0, 0, 0}}, */
	/* {"./{,obj,include}/\*", TEST_FLAGS | GLOBUX_BRACE, {0, NULL, 0, 0, 0}}, */
	/* {"/usr/{bin,share}", TEST_FLAGS | GLOBUX_BRACE, {0, NULL, 0, 0, 0}}, */
	/* {"/usr/{bin,share}/\*", TEST_FLAGS | GLOBUX_BRACE, {0, NULL, 0, 0, 0}}, */
};



static void get_flags_string(int flags, char *buf)
{
	char *s;
	size_t len;

	if (!flags) {
		strcpy(buf, "0");
		return;
	}

	s = buf;
	for (int i = 0; i <= 14; i++) {
		if ((flags & (1 << i))) {
			len = strlen(glob_flags_strings[i]);
			memcpy(s, glob_flags_strings[i], len);
			memcpy(s + len, " | ", 3);
			s += len + 3;
		}
	}

	*(s - 3) = 0;
}

static void get_argv_string(char **av, char *buf)
{
	char *s;
	size_t len;

	if (!av || !*av) {
		*buf = 0;
		return;
	}

	s = buf;
	for (; *av; av++) {
		len = strlen(*av);
		memcpy(s, *av, len);
		memcpy(s + len, ", ", 2);
		s += len + 2;
	}

	*(s - 2) = 0;
}

static void get_debug_string(char const *pat, int flags, int ctrl, int test, \
								  t_glob *glob_input, t_glob *glob_test, glob_t *glob_ctrl)
{
	get_flags_string(flags, flags_buffer);
	get_flags_string(glob_input->gl_flags, flags_input_buffer);
	get_flags_string(glob_test->gl_flags, flags_test_buffer);
	get_flags_string(glob_ctrl->gl_flags, flags_ctrl_buffer);
	get_argv_string(glob_input->gl_pathv, argv_input_buffer);
	get_argv_string(glob_test->gl_pathv, argv_test_buffer);
	get_argv_string(glob_ctrl->gl_pathv, argv_ctrl_buffer);

	sprintf(
		print_buffer,
		CLR_GREEN "INPUT:" CLR_RESET "\n"
		"    pattern=%s,\n"
		"    flags=%s,\n"
		"    pglob={\n"
		"        gl_pathc:%zu,\n"
		"        gl_pathv:[%s],\n"
		"        gl_offs:%zu,\n"
		"        gl_flags=%s,\n"
		"    }\n"

		CLR_YELLOW "CTRL:" CLR_RESET "\n"
		"    return=%s,\n"
		"    pglob={\n"
		"        gl_pathc:%zu,\n"
		"        gl_pathv:[%s],\n"
		"        gl_offs:%zu,\n"
		"        gl_flags=%s,\n"
		"    }\n"

		CLR_RED "TEST:" CLR_RESET "\n"
		"    return=%s,\n"
		"    pglob={\n"
		"        gl_pathc:%zu,\n"
		"        gl_pathv:[%s],\n"
		"        gl_offs:%zu,\n"
		"        gl_flags=%s,\n"
		"    }\n",

		pat,
		flags_buffer,
		glob_input->gl_pathc,
		argv_input_buffer,
		glob_input->gl_offs,
		flags_input_buffer,

		((size_t)ctrl + 1 > sizeof(glob_ret_strings) / sizeof(*glob_ret_strings)) ? \
			"UNKOWN_RETURN_CODE" : glob_ret_strings[ctrl],
		glob_ctrl->gl_pathc,
		argv_ctrl_buffer,
		glob_ctrl->gl_offs,
		flags_ctrl_buffer,

		((size_t)test + 1 > sizeof(glob_ret_strings) / sizeof(*glob_ret_strings)) ? \
			"UNKOWN_RETURN_CODE" : glob_ret_strings[test],
		glob_test->gl_pathc,
		argv_test_buffer,
		glob_test->gl_offs,
		flags_test_buffer
	);
}

static int compare_argv(char **a, char **b)
{
	for (int i = 0; a && a[i]; i++) {
		if (strcmp(a[i], b[i]))
			return 42;
	}
	return 0;
}

static void glob_testux(char const *pat, int flags, t_glob *pglob)
{
	t_glob input;
	int ret, expected;

	memcpy(&input, pglob, sizeof(t_glob));

	expected = glob(pat, flags, NULL, &ctrl_glob_struct);
	ret = ft_glob(pat, flags, pglob);

	get_debug_string(pat, flags, expected, ret, &input, pglob, &ctrl_glob_struct);

	MU_ASSERT(
		ret == expected,
		"glob return mismatch:\n" "%s",
		print_buffer
	);
	if (ret != expected)
		return;

	MU_ASSERT(
		pglob->gl_offs == ctrl_glob_struct.gl_offs,
		"t_glob->gl_offs mismatch:\n" "%s",
		print_buffer
	);
	if (pglob->gl_offs != ctrl_glob_struct.gl_offs)
		return;

	/* MU_ASSERT( */
	/* 	pglob->gl_flags == ctrl_glob_struct.gl_flags, */
	/* 	"t_glob->gl_flags mismatch:\n" "%s", */
	/* 	print_buffer */
	/* ); */
	/* if (pglob->gl_flags != ctrl_glob_struct.gl_flags) */
	/* 	return; */

	MU_ASSERT(
		pglob->gl_pathc == ctrl_glob_struct.gl_pathc,
		"t_glob->gl_pathc mismatch:\n" "%s",
		print_buffer
	);
	if (pglob->gl_pathc != ctrl_glob_struct.gl_pathc)
		return;

	MU_ASSERT(
		!compare_argv(pglob->gl_pathv, ctrl_glob_struct.gl_pathv),
		"t_glob->gl_pathv mismatch:\n" "%s",
		print_buffer
	);
}

void test_glob()
{
	for (int flag = 0; flag <= GLOB_NOCHECK; flag += GLOB_NOCHECK) {
		for (unsigned int i = 0; i < sizeof(test_glob_arr) / sizeof(struct s_test_glob); i++) {
			ctrl_glob_struct.gl_pathc = test_glob_arr[i].pglob.gl_pathc;
			ctrl_glob_struct.gl_pathv = test_glob_arr[i].pglob.gl_pathv; //TODO
			ctrl_glob_struct.gl_offs = test_glob_arr[i].pglob.gl_offs;
			ctrl_glob_struct.gl_flags = test_glob_arr[i].pglob.gl_flags;

			glob_testux(
				test_glob_arr[i].pattern,
				test_glob_arr[i].flags | flag,
				&(test_glob_arr[i].pglob)
			);
			globfree(&ctrl_glob_struct);
			ft_globfree(&test_glob_arr[i].pglob);
		}
	}

}
