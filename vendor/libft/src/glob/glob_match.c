/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 21:09:16 by mc                #+#    #+#             */
/*   Updated: 2018/02/13 11:42:25 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob_match - glob util function to check if a pattern actually match
*/

#include "libft/glob.h"
#include "glob_match.h"

#ifdef DEBUG_MODE
char const *g_pat = NULL;
char const *g_str = NULL;
# define _DEBUGUX(_header, _pat, _str) do {						\
	_DEBUG(_header ": pat[%d]: %c", (int)(_pat - g_pat), *_pat); \
	_DEBUG(_header ": str[%d]: %c\n", (int)(_str - g_str), *_str); \
} while (0)
#else
# define _DEBUGUX(_header, _pat, _str) do {} while (0)
#endif


static t_bool handle_rev_char_class(char const *pat, char const *str, int flags, \
								t_bool matched)
{
	_DEBUG("REV_CHAR_CLASS: match: %d", matched);
	_DEBUGUX("REV_CHAR_CLASS", pat, str);

	if (!*pat)
		return FALSE; //TODO: unmatched bracket :/

	if (*pat == '[' && *(pat + 1) == ']')
		return matched & (*str != *pat) ? \
			glob_match(pat + 2, str + 1, flags) : FALSE;

	if (*pat == ']' && *(pat - 2) != '[')
		return matched ? glob_match(pat + 1, str + 1, flags) : FALSE;

	if (*(pat + 1) == '-' && *(pat + 2) != ']') //TODO: overflow on pat?
		return handle_rev_char_class(pat + 3, str, flags, \
						matched & (*str <= *pat || *str >= *(pat + 2)));

	return handle_rev_char_class(pat + 1, str, flags, \
						matched & (*str != *pat));
}

static t_bool handle_char_class(char const *pat, char const *str, int flags, \
								t_bool matched)
{
	_DEBUG("CHAR_CLASS: match: %d", matched);
	_DEBUGUX("CHAR_CLASS", pat, str);

	if (!*pat)
		return FALSE; //TODO: unmatched bracket :/

	if (*pat == '[' && *(pat + 1) == ']')
		return matched | (*str == *pat) ? \
			glob_match(pat + 2, str + 1, flags) : FALSE;

	if (*pat == ']' && *(pat - 1) != '[')
		return matched ? glob_match(pat + 1, str + 1, flags) : FALSE;

	if (*(pat + 1) == '-' && *(pat + 2) != ']')
		return handle_char_class(pat + 3, str, flags, \
						matched | (*str >= *pat && *str <= *(pat + 2)));

	return handle_char_class(pat + 1, str, flags, \
						matched | (*str == *pat));
}

static t_bool handle_str_wildcard(char const *pat, char const *str, int flags, \
								  int depth)
{
	_DEBUGUX("STR_WILDCARD", pat, str);

	if (depth > MAX_DEPTH)
		return FALSE;

	if (glob_match(pat, str, flags)) //BOOOOM BABY!
		return TRUE;

	if (!*str)
		return glob_match(pat, str, flags);

	return handle_str_wildcard(pat, str + 1, flags, depth + 1);
}

//TODO: triple-check overflows
t_bool glob_match(char const *pat, char const *str, int flags)
{
# ifdef DEBUG_MODE
	if (!g_pat) g_pat = pat;
	if (!g_str) g_str = str;
#endif
	_DEBUGUX("GLOB_MATCH", pat, str);

	//TODO: set GLOB_MAGCHAR

	if (*pat == '\\' && !(flags & GLOB_NOESCAPE))
		return *(pat + 1) == *str ? glob_match(pat + 2, str + 1, flags) : FALSE;

	if (*pat == '[')
	{
		if (*(pat + 1) == '!' || *(pat + 1) == '^')
			return handle_rev_char_class(pat + 2, str, flags, TRUE);
		else
			return handle_char_class(pat + 1, str, flags, FALSE);
	}

	if (*pat == '*')
		return handle_str_wildcard(pat + 1, str, flags, 1);

	if (*pat == '?')
		return *str ? glob_match(pat + 1, str + 1, flags) : FALSE;

	if (*pat != *str)
		return FALSE;

	if (!*pat)
		return !*str ? TRUE : FALSE;

	return glob_match(pat + 1, str + 1, flags);
}
