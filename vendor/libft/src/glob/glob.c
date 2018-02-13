/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:54:42 by mc                #+#    #+#             */
/*   Updated: 2018/02/13 02:27:15 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** globctor, globdtor -
** find pathnames matching a pattern, free memory from globctor()
*/

#include "libft/glob.h"
#include "glob_climb_tree.h"

static int super_cmp(const void *a, const void *b, size_t n)
{
	(void)n; //this is the of one element eheh
	return ft_strcmp((char *)a, (char *)b);
}

static int copy_match_to_glob_struct(t_match *match_list, t_glob *pglob)
{
/*
	if ((pglob->gl_flags & GLOB_DOOFFS))
		handle_offset();

	if ((pglob->gl_flags & GLOB_APPEND))
		append_to_something(); //TODO: ???

	copy();

*/
	if (!(pglob->gl_flags & GLOB_NOSORT))
		ft_shellsort(pglob->gl_pathv, pglob->gl_pathc, sizeof(char *), super_cmp);

	(void)match_list; //TODO

	return GLOB_SUCCESS;
}

int		globctor(const char *pattern, int flags, t_glob *pglob)
{
	t_match *match_list;
	int		ret;

	if ((flags & ~__GLOB_FLAGS))
		return GLOB_NOSYS;

	pglob->gl_flags = flags;
	pglob->gl_pathv = NULL;
	pglob->gl_pathc = 0;

	match_list = NULL;
	ret = glob_climb_tree(pattern, flags, &match_list);
	if (ret != GLOB_SUCCESS)
		return ret;

	if (!copy_match_to_glob_struct(match_list, pglob))
		return GLOB_NOSPACE;

	return GLOB_SUCCESS;
}

void	globdtor(t_glob *pglob)
{
	char **av;

	av = pglob->gl_pathv + pglob->gl_offs;
	while (*av)
		free(av++);
	free(pglob->gl_pathv);
}
