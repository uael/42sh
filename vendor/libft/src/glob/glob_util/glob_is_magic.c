/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_is_magic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:36:27 by mc                #+#    #+#             */
/*   Updated: 2018/02/23 20:36:35 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** it is!
*/

#include "glob_util.h"

static t_bool		is_escaped(char const *pattern, char const *pat, int flags)
{
	if ((flags & GLOBUX_NOESCAPE))
		return (FALSE);
	return ((t_bool)(pat != pattern && *(pat - 1) == '\\'));
}

char const			*is_there_a_closing_bracket(char const *pattern, \
												int flags, char c, char o)
{
	char const		*pat;
	int				depth;

	pat = pattern;
	depth = 0;
	while (*pat)
	{
		if (*pat == o)
			++depth;
		else if (*pat == c && !--depth && pat != pattern + 1)
		{
			if (!is_escaped(pattern, pat, flags))
				return (pat);
			++depth;
		}
		pat++;
	}
	return (NULL);
}

static char	const	*previous_dir(char *magic_buf, char const *pattern, \
								char const *pat)
{
	size_t			len;

	while (pat != pattern)
	{
		if (*pat == '/')
		{
			len = (size_t)(pat - pattern) + 1;
			if (len + 1 > NAME_MAX)
				return (pattern);
			ft_memcpy(magic_buf, pattern, len);
			*(magic_buf + len + 1) = '\0';
			return (magic_buf);
		}
		pat--;
	}
	return (pattern);
}

char const			*is_magic(char *magic_buf, char const *pattern, int *flags)
{
	char	const *pat;

	pat = pattern;
	while (*pat)
	{
		if (*pat == '*' || *pat == '?')
		{
			if (!is_escaped(pattern, pat, *flags))
			{
				*flags |= GLOBUX_MAGCHAR;
				return (previous_dir(magic_buf, pattern, pat));
			}
		}
		else if (*pat == '[')
		{
			if (!is_escaped(pattern, pat, *flags) \
				&& is_there_a_closing_bracket(pat, *flags, ']', '['))
			{
				*flags |= GLOBUX_MAGCHAR;
				return (previous_dir(magic_buf, pattern, pat));
			}
		}
		pat++;
	}
	return (NULL);
}
