/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 21:09:16 by mc                #+#    #+#             */
/*   Updated: 2018/02/16 11:15:14 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob_match - glob util function to check if a pattern actually match
*/

#include "libft/ft_glob.h"
#include "glob_match.h"

static t_bool handle_rev_char_class(char const *pat, char const *str, int flags, \
								t_bool matched)
{
	if (!*pat)
		return (FALSE); //TODO: unmatched bracket :/

	if (*pat == '[' && *(pat + 1) == ']')
		return matched & (*str != *pat) ? \
			glob_match(pat + 2, str + 1, flags) : FALSE;

	if (*pat == ']' && *(pat - 2) != '[')
		return (matched ? glob_match(pat + 1, str + 1, flags) : FALSE);

	if (*(pat + 1) == '-' && *(pat + 2) != ']') //TODO: overflow on pat?
		return handle_rev_char_class(pat + 3, str, flags, \
						matched & (*str <= *pat || *str >= *(pat + 2)));

	return handle_rev_char_class(pat + 1, str, flags, \
						matched & (*str != *pat));
}

static t_bool handle_char_class(char const *pat, char const *str, int flags, \
								t_bool matched)
{
	if (!*pat)
		return (FALSE); //TODO: unmatched bracket :/

	if (*pat == '[' && *(pat + 1) == ']')
		return matched | (*str == *pat) ? \
			glob_match(pat + 2, str + 1, flags) : FALSE;

	if (*pat == ']' && *(pat - 1) != '[')
		return (matched ? glob_match(pat + 1, str + 1, flags) : FALSE);

	if (*(pat + 1) == '-' && *(pat + 2) != ']')
		return handle_char_class(pat + 3, str, flags, \
						matched | (*str >= *pat && *str <= *(pat + 2)));

	return handle_char_class(pat + 1, str, flags, \
						matched | (*str == *pat));
}

static t_bool handle_str_wildcard(char const *pat, char const *str, int flags, \
								  int depth)
{
	if (depth > MAX_DEPTH)
		return (FALSE);

	if (!*pat)
		return (TRUE);

	if (glob_match(pat, str, flags)) //BOOOOM BABY!
		return (TRUE);

	if (!*str)
		return (glob_match(pat, str, flags));

	return (handle_str_wildcard(pat, str + 1, flags, depth + 1));
}

t_bool glob_match(char const *pat, char const *str, int flags)
{
	if (*pat == '\\' && !(flags & GLOBUX_NOESCAPE))
		return (*(pat + 1) == *str ? glob_match(pat + 2, str + 1, flags) : FALSE);

	if (*pat == '[')
	{
		if (*(pat + 1) == '!' || *(pat + 1) == '^')
			return (handle_rev_char_class(pat + 2, str, flags, TRUE));
		else
			return (handle_char_class(pat + 1, str, flags, FALSE));
	}

	if (*pat == '*')
		return (handle_str_wildcard(pat + 1, str, flags, 1));

	if (*pat == '?')
		return (*str ? glob_match(pat + 1, str + 1, flags) : FALSE);

	if (*pat != *str)
		return (FALSE);

	if (!*pat)
		return (!*str ? TRUE : FALSE);

	return (glob_match(pat + 1, str + 1, flags));
}
