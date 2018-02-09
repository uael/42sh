/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minunit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:32:38 by mcanal            #+#    #+#             */
/*   Updated: 2018/02/08 23:45:08 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "super_test_3000.h"

static void suites_me(char *search)
{
	MU_TEST_SUITE suite_42sh = {
		{test_env, "env"},
		{test_glob, "glob"},
	};

	if (search) {
		int test_run_before = g_tests_run; //hmmm...

		MU_RUN_TEST_FROM_SUITE(search, suite_42sh);

		if (test_run_before == g_tests_run) {
			fprintf(stderr, "+ Test %s: "CLR_RED"not found\n"CLR_RESET, search);
			exit(EXIT_FAILURE);
		}
	} else {
		MU_RUN_SUITE(suite_42sh, "42sh");
	}
}

MU_HAI(); //yep, this is really ugly :/

int main(int ac, char **av) //TODO: --help
{
	setbuf(stdout, NULL); /* TODO: find a better place for this */
	if (ac == 1) {
		suites_me(NULL);
	} else {
		while (*++av) {
			suites_me(*av);
		}
		printf("\n");
	}

	MU_KTHXBYE();
	return EXIT_SUCCESS;
}
