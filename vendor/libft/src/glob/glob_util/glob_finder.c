/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 13:20:58 by mc                #+#    #+#             */
/*   Updated: 2018/02/25 13:21:29 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_util.h"

char const	*glob_find_comma(char const *pat, char const *pat_end)
{
	if (pat >= pat_end)
		return (NULL);
	if (*pat == ',')
		return (pat);
	return (glob_find_comma(pat + 1, pat_end));
}

char const	*glob_find_opening_brace(char const *pat, char const *pat_start)
{
	if (!*pat)
		return (NULL);
	if (*pat == '{' && (pat == pat_start || *(pat - 1) != '\\'))
		return (pat);
	return (glob_find_opening_brace(pat + 1, pat_start));
}
