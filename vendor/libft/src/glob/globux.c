/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:54:42 by mc                #+#    #+#             */
/*   Updated: 2018/02/23 17:33:24 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globux.h"

/*
** ft_glob, ft_globfree -
** find pathnames matching a pattern, free memory from ft_glob()
*/

static char		**alloc_pathv(t_glob *pglob)
{
	if ((pglob->gl_flags & GLOBUX_DOOFFS))
	{
		if (!(pglob->gl_pathv = malloc(sizeof(char *) \
								* (pglob->gl_pathc + pglob->gl_offs + 1))))
			return (NULL);
		return (pglob->gl_pathv + pglob->gl_offs);
	}
	else
	{
		if (!(pglob->gl_pathv = malloc(sizeof(char *) * (pglob->gl_pathc + 1))))
			return (NULL);
		return (pglob->gl_pathv);
	}
}

static int		copy_match_to_glob_struct(t_match *match_list, t_glob *pglob)
{
	char	**av;

	pglob->gl_pathc = list_len(match_list);
	if (!(av = alloc_pathv(pglob)))
	{
		matchdtor(match_list);
		return (GLOBUX_NOSPACE);
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
	return (GLOBUX_SUCCESS);
}

static void		glbnvctor(t_glob_env *glob_env, char const *pattern, int *flags, \
						t_glob *pglob)
{
	ft_bzero(glob_env, sizeof(t_glob_env));
	glob_env->pattern = pattern;
	glob_env->flags = flags;
	pglob->gl_flags = *flags;
}

int				ft_glob(const char *pattern, int flags, t_glob *pglob)
{
	t_glob_env		glob_env;
	int				ret;

	if ((flags & ~__GLOBUX_FLAGS))
		return (GLOBUX_NOSYS);
	if (!(flags & GLOBUX_NOCHECK) && !*pattern)
		return (GLOBUX_NOMATCH);
	glbnvctor(&glob_env, pattern, &(pglob->gl_flags), pglob);
	if ((ret = glob_climb_tree(&glob_env)))
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
		if (!(glob_env.match_list = matchctor(pattern, ft_strlen(pattern), \
				!(flags & GLOBUX_NOESCAPE))))
			return (GLOBUX_NOSPACE);
	}
	return (copy_match_to_glob_struct(glob_env.match_list, pglob));
}

void			ft_globfree(t_glob *pglob)
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
		free((t_byte *)(*av) - sizeof(t_match) + sizeof(t_byte *));
		av++;
	}
	free(pglob->gl_pathv);
	pglob->gl_pathv = NULL;
}
