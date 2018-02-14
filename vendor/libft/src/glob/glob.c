/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:54:42 by mc                #+#    #+#             */
/*   Updated: 2018/02/14 23:24:54 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** globctor, globdtor -
** find pathnames matching a pattern, free memory from globctor()
*/

#include "libft/ft_glob.h"
#include "glob_climb_tree.h"

static int super_cmp(const void *a, const void *b, size_t n)
{
	(void)n; //this is the size of one element eheh
	return ft_strcmp((char *)a, (char *)b);
}

static t_bool copy_match_to_glob_struct(t_match *match_list, t_glob *pglob)
{
	char	**av;

/*
	if ((pglob->gl_flags & GLOBUX_APPEND))
		append_to_something(); //TODO: ???
*/
	pglob->gl_pathc = list_len(match_list); //TODO: find another way

	if ((pglob->gl_flags & GLOBUX_DOOFFS))
	{
		if (!(pglob->gl_pathv = malloc(sizeof(char *) *
								   (pglob->gl_pathc + pglob->gl_offs + 1))))
			return FALSE;
		av = pglob->gl_pathv + pglob->gl_offs;
	}
	else
	{
		if (!(pglob->gl_pathv = malloc(sizeof(char *) * (pglob->gl_pathc + 1))))
			return FALSE;
		av = pglob->gl_pathv;
	}

	while (match_list)
	{
		*av = (char *)(match_list->buf);
		av++;
		match_list = match_list->next;
	}
	*av = NULL;

	if (!(pglob->gl_flags & GLOBUX_NOSORT))
		ft_shellsort(pglob->gl_pathv, pglob->gl_pathc, sizeof(char *), super_cmp);

	return TRUE;
}

//TODO: handle errors libft tools?
int		globctor(const char *pattern, int flags, t_glob *pglob)
{
	t_match *match_list;
	int		ret;

	if (!*pattern)
		return GLOBUX_NOMATCH;
	if ((flags & ~__GLOBUX_FLAGS))
		return GLOBUX_NOSYS;
	//TODO: handle weird pglob?

	pglob->gl_flags = flags;
	pglob->gl_pathv = NULL;
	pglob->gl_pathc = 0;

	match_list = NULL;
	ret = glob_climb_tree(pattern, flags, &match_list);
	if (ret != GLOBUX_SUCCESS)
	{
		matchdtor(match_list);
		return ret;
	}

	if (!match_list)
		return GLOBUX_NOMATCH;

	if (!copy_match_to_glob_struct(match_list, pglob))
	{
		matchdtor(match_list);
		return GLOBUX_NOSPACE;
	}

	return GLOBUX_SUCCESS;
}

void	globdtor(t_glob *pglob)
{
	char **av;

	if ((pglob->gl_flags & GLOBUX_DOOFFS))
		av = pglob->gl_pathv + pglob->gl_offs;
	else
		av = pglob->gl_pathv;

	while (*av)
	{
		//TODO: doc + test
		free((t_byte *)(*av) - sizeof(t_match) + sizeof(t_byte)); // magic list!
		av++;
	}

	free(pglob->gl_pathv);
}
