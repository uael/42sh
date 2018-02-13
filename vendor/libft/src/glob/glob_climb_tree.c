/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:23:43 by mc                #+#    #+#             */
/*   Updated: 2018/02/13 13:09:20 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob_climb_tree - glob util function to check recursively a directory tree
*/

#include "libft/glob.h"
#include "glob_climb_tree.h"

int tree_climber(char const *dir, char const *pattern, int flags, t_match **match_list, int depth); //TODO: ooops

/*
static char **handle_brace_expansion(char const *pattern)
{
	//TODO
	(void)pattern;

	return (char **)42;
}
*/

static int tree_climber_loop(char const *file, char const *pattern, int flags, t_match **match_list, int depth) //TODO: ooops
{
/*
	int			ret;
	t_match		*match;

	if ((flags & GLOB_ONLYDIR) && is_a_dir(file))
		return GLOB_SUCCESS;

	//TODO: should we reset the GLOB_MAGCHAR flag?
	if (!glob_match(
		'/' + subpats[:depth - len(subpats)].join('/'),
			// re-join pattern from the begin to i
		file
	))
		return GLOB_SUCCESS;

	if ((flags & GLOB_PERIOD) && !(flags & GLOB_MAGCHAR) && *file == '.')
		return GLOB_SUCCESS;

	if (is_a_dir_or_link(file))
	{
		ret = tree_climber(file, pattern, flags, match_list, depth - 1); //BOOOOM BABY!
		if (ret != GLOB_SUCCESS)
			return ret;
	}

	if (!(match = matchctor(file, ft_strlen(file))))
		return GLOB_NOSPACE;
	add_match_to_list(match, match_list);
*/

	return GLOB_SUCCESS;
}

int tree_climber(char const *dir, char const *pattern, int flags, t_match **match_list, int depth)
{
/*
	int			ret;

	if (!depth)
		return GLOB_SUCCESS;

	files[] = ls(dir)
	if (read_error && (flags & GLOB_ERR))
		return GLOB_ABORTED;

	subpats[] = pattern.split('/');

	for (file in files)
	{
		ret = tree_climber_loop(file, pattern, flags, match_list, depth);
		if (ret != GLOB_SUCCESS)
			return ret;
	}
*/

	return GLOB_SUCCESS;
}

//TODO: test
int glob_climb_tree(char const *pattern, int flags, t_match **match_list)
{
	//TODO: flags: we might want to pass the whole t_glob struct instead
/*
	handle_flags(GLOB_TILDE | GLOB_TILDE_CHECK)

	if '{' in pattern and GLOB_BRACE:
		patterns[] = handle_brace_expansion(pattern)
			for pat in patterns:
				if not glob_climb_tree(patn flags)
					return false;
*/
	char const	*search_start;
	int			depth;
	int			ret;

	depth = 1;
	search_start = pattern;
	while (*search_start)
	{
		if (*search_start == '/')
			depth++;
		search_start++;
	}

	if (depth > MAX_DEPTH)
		return GLOB_NOSPACE;
	else if (depth == 1)
		search_start = pattern; //TODO: concat $PWD instead?
	else
		while (*search_start != '/')
			search_start--;

	ret = tree_climber(search_start, pattern, flags, match_list, depth);
/*
	if GLOB_NOCHECK and not files:
		return pattern
	if GLOB_NOMAGIC and not GLOB_MAGCHAR:
		return pattern
*/
	return ret;
}
