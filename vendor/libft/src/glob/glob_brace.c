/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_brace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mc.maxcanal@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 17:55:44 by mcanal            #+#    #+#             */
/*   Updated: 2018/02/26 01:13:51 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_climb_tree.h"

static int			glob_copy_pattern_and_boom(t_glob_env *e, \
						char const *pat_end, char const *pat, size_t pat_size)
{
	char		brace_buf[PATH_MAX];
	char const	*pat_save;
	size_t		before_size;
	size_t		after_size;

	before_size = glob_find_opening_brace(e->pattern, e->pattern) - e->pattern;
	after_size = ft_strlen(pat_end);
	if (before_size + pat_size + after_size + 1 > PATH_MAX)
		return (GLOBUX_NOSPACE);
	ft_memcpy(brace_buf, e->pattern, before_size);
	ft_memcpy(brace_buf + before_size, pat, pat_size);
	ft_memcpy(brace_buf + before_size + pat_size, pat_end, after_size + 1);
	pat_save = e->pattern;
	e->pattern = brace_buf;
	*(e->flags) |= GLOBUX_APPEND;
	glob_climb_tree(e);
	e->pattern = pat_save;
	return (-1);
}

static int			glob_find_sub_brace(t_glob_env *e, char const *comma, \
										char const *pat, char const *pat_end)
{
	if (!comma)
		return (glob_copy_pattern_and_boom(e, \
							pat_end + 1, pat + 1, (size_t)(pat_end - pat) - 1));
	glob_copy_pattern_and_boom(e, \
						pat_end + 1, pat + 1, (size_t)(comma - pat) - 1);
	return (glob_find_sub_brace(e, glob_find_comma(comma + 1, pat_end), \
								comma, pat_end));
}

static int			glob_check_brace(t_glob_env *e)
{
	char const	*pat_start;
	char const	*pat_end;
	char const	*comma;

	if (!(pat_start = glob_find_opening_brace(e->pattern, e->pattern)))
		return (GLOBUX_SUCCESS);
	if (!(pat_end = is_there_a_closing_bracket(pat_start, *(e->flags), '}')))
		return (GLOBUX_SUCCESS);
	if (!(comma = glob_find_comma(pat_start + 1, pat_end)))
		return (GLOBUX_SUCCESS);
	return (glob_find_sub_brace(e, comma, pat_start, pat_end));
}

int					glob_brace(t_glob_env *e)
{
	if (!(*(e->flags) & GLOBUX_BRACE))
		return (GLOBUX_SUCCESS);
	return (glob_check_brace(e));
}
