/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:23:43 by mc                #+#    #+#             */
/*   Updated: 2018/02/12 00:02:52 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob_climb_tree - glob util function to check recursively a directory tree
*/

#include "libft/glob.h"
#include "glob_match.h"
#include "glob_climb_tree.h"

static char **handle_brace_expansion(char const *pattern)
{
	//TODO
	(void)pattern;

	return (char **)42;
}

static t_bool tree_climber(char const *dir, char const *pattern, int depth, int flags)
{
	//TODO: define MAX_DEPTH
/*
	ret[] = []  //TODO: choose data-struct: linked list?

	subpats[] = pattern.split('/')

	files[] = ls(dir)
	if read_error and GLOB_ERR:
		return false

	// remove non-matching files
	for(file in files):
		if GLOB_ONLYDIR and is_a_dir(file):
			files.pop(file)

		if not GLOB_PERIOD and GLOB_MAGCHAR and file[0] == '.':
			files.pop(file)

		if not glob_match(
			'/' + subpats[:depth - len(subpats)].join('/'),
				// re-join pattern from the begin to i
			file
		):
			files.pop(file)

	//no more recursion needed, just return matching files
	if depth == 1:
		return files

	// loop on matching dirs/links
	for(file in files):
		if is_a_dir_or_link(file):
			ret += tree_climber(
				file,
				pattern,
				depth - 1
			)

	return ret  //TODO: return mismatch :o
*/
	(void)dir; //TODO
	(void)pattern; //TODO
	(void)depth; //TODO
	(void)flags; //TODO
	return 42; //TODO
}

t_bool glob_climb_tree(char const *pattern, int flags)
{
	//TODO: flags: we might want to pass the whole t_glob struct instead
/*
	handle_flags(GLOB_TILDE | GLOB_TILDE_CHECK)

	if '{' in pattern and GLOB_BRACE:
		patterns[] = handle_brace_expansion(pattern)
			for pat in patterns:
				if not glob_climb_tree(patn flags)
					return false;

	char *search_start = NULL
	char *ptr = pattern

	// something like: search_start = dirname(pattern)  [+ handle GLOB_MAGCHAR]
	while (*ptr && *ptr != GLOB_CHAR)
		ptr++;
	if (!*ptr and GLOB_NOMAGIC)
		return false
	flags |= GLOB_MAGCHAR
	while (*ptr != '/')
		ptr--;
	*ptr = 0;
	search_start = strdup(pattern)
	*ptr = '/';

	matched_files = check_dir_loop(
		search_start,
			// first dir we're gonna search on
		pattern,
			// the whole pattern
		len(pattern.split('/')) - len(dir.split('/'))
			// search depth
	)

	return matched_files  //TODO: return mismatch :o
*/
	(void)pattern; //TODO
	(void)flags; //TODO
	return 42; //TODO
}
