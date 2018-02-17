/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_is_magic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:36:27 by mc                #+#    #+#             */
/*   Updated: 2018/02/16 14:39:17 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** it is!
*/

#include "libft/ft_glob.h"
#include "glob_climb_tree.h"

static t_bool		is_escaped(char const *pattern, char const *pat, int flags)
{
	if ((flags & GLOBUX_NOESCAPE))
		return (FALSE);
	return (pat != pattern && *(pat - 1) == '\\');
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
				return (TRUE);
		}

		pat++;
	}

	return (FALSE);
}

static char const	*previous_dir(char const *pattern, char const *pat)
{
	static	char	magic_buf[NAME_MAX]; //TODO: berk
	size_t			len;

	while (pat != pattern)
	{
		if (*pat == '/')
		{
			len = (size_t)(pat - pattern);
			if (len + 1 > NAME_MAX)
				return (NULL);
			ft_memcpy(magic_buf, pattern, len);
			*(magic_buf + len + 1) = '\0';
			return (magic_buf);
		}
		pat--;
	}

	return (NULL);
}


char const			*is_magic(char const *pattern, int *flags)
{
	char const *pat;

	pat = pattern;
	while (*pat)
	{
		if (*pat == '*' || *pat == '?')
		{
			if (!is_escaped(pattern, pat, *flags))
			{
				*flags |= GLOBUX_MAGCHAR;
				return (previous_dir(pattern, pat));
			}
		}
		else if (*pat == '[')
		{
			if (!is_escaped(pattern, pat, *flags) \
					&& is_there_a_closing_bracket(pat, *flags))
			{
				*flags |= GLOBUX_MAGCHAR;
				return (previous_dir(pattern, pat));
			}
		}

		pat++;
	}

	return (NULL);
}
