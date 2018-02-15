/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_is_magic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:36:27 by mc                #+#    #+#             */
/*   Updated: 2018/02/15 14:05:59 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** it is!
*/

#include "libft/ft_glob.h"
#include "glob_match.h"

static t_bool		is_escaped(char const *pattern, char const *pat, int flags)
{
	return !(flags & GLOBUX_NOESCAPE) && pat != pattern && *(pat - 1) == '\\';
}

static t_bool		is_there_a_closing_bracket(char const *pattern, int flags)
{
	char const *pat;

	pat = pattern;
	while (*pat)
	{
		if (*pat == ']' && pat != pattern + 1)
		{
			if (!is_escaped(pattern, pat, flags))
				return TRUE;
		}

		pat++;
	}

	return FALSE;
}

static char const	*previous_dir(char const *pattern, char const *pat)
{
	while (pat != pattern)
	{
		if (*pat == '/')
			return pat; //TODO: pat - 1?
		pat--;
	}

	return pat;
}


char const			*is_magic(char const *pattern, int flags)
{
	char const *pat;

	pat = pattern;
	while (*pat)
	{
		if (*pat == '*' || *pat == '?')
		{
			if (!is_escaped(pattern, pat, flags))
				return previous_dir(pattern, pat);
		}
		else if (*pat == '[')
		{
			if (!is_escaped(pattern, pat, flags) \
					&& is_there_a_closing_bracket(pat, flags))
				return previous_dir(pattern, pat);
		}

		pat++;
	}

	return NULL;
}
