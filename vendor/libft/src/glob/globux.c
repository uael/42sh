/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:54:42 by mc                #+#    #+#             */
/*   Updated: 2018/02/20 17:23:39 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** globctor, globdtor -
** find pathnames matching a pattern, free memory from globctor()
*/

#include "globux.h"

static int		super_cmp(const void *a, const void *b, size_t n)
{
	(void)n;
	return (ft_strcmp(*(char **)a, *(char **)b));
}

static t_bool	copy_match_to_glob_struct(t_match *match_list, t_glob *pglob)
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
			return (FALSE);
		av = pglob->gl_pathv + pglob->gl_offs;
	}
	else
	{
		if (!(pglob->gl_pathv = malloc(sizeof(char *) * (pglob->gl_pathc + 1))))
			return (FALSE);
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
		ft_shellsort((pglob->gl_flags & GLOBUX_DOOFFS) ? \
					pglob->gl_pathv : pglob->gl_pathv + pglob->gl_offs, \
					pglob->gl_pathc, sizeof(char *), super_cmp);

	return (TRUE);
}

static void		glbnvctor(t_glob_env *glob_env, char const *pattern, int *flags)
{
	ft_bzero(glob_env, sizeof(t_glob_env));
	glob_env->pattern = pattern;
	glob_env->flags = flags;
}

//TODO: handle errors with libft tools?
int				globctor(const char *pattern, int flags, t_glob *pglob)
{
	t_glob_env		glob_env;
	int				ret;
	//TODO: set GLOB_NOCHECK | GLOB_ONLYDIR in pglob when ???

	if ((flags & ~__GLOBUX_FLAGS))
		return (GLOBUX_NOSYS);
	if (!(flags & GLOBUX_NOCHECK) && !*pattern)
		return (GLOBUX_NOMATCH);
	//TODO: handle weird pglob?

	pglob->gl_flags = flags;

	glbnvctor(&glob_env, pattern, &(pglob->gl_flags));
	ret = glob_climb_tree(&glob_env);
	if (ret != GLOBUX_SUCCESS)
	{
		matchdtor(glob_env.match_list);
		return (ret);
	}

	if (!glob_env.match_list)
	{
		if (!(flags & GLOBUX_NOCHECK))
		{
			pglob->gl_flags = (pglob->gl_flags & ~GLOBUX_MAGCHAR);
			return (GLOBUX_NOMATCH);
		}

		if (!(glob_env.match_list = matchctor(pattern, ft_strlen(pattern))))
			return (GLOBUX_NOSPACE);
	}

	if (!copy_match_to_glob_struct(glob_env.match_list, pglob))
	{
		matchdtor(glob_env.match_list);
		return (GLOBUX_NOSPACE);
	}

	return (GLOBUX_SUCCESS);
}

void			globdtor(t_glob *pglob)
{
	char	**av;

	if (!pglob->gl_pathv)
		return ;
	if ((pglob->gl_flags & GLOBUX_DOOFFS))
		av = pglob->gl_pathv + pglob->gl_offs;
	else
		av = pglob->gl_pathv;
	while (pglob->gl_pathc--)
	{
		free((t_byte *)(*av) - sizeof(t_match) + sizeof(t_byte *)); //TODO: doc
		av++;
	}
	free(pglob->gl_pathv);
	pglob->gl_pathv = NULL;
}
