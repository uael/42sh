/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:23:43 by mc                #+#    #+#             */
/*   Updated: 2018/02/13 09:37:21 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob_climb_tree - glob util function to check recursively a directory tree
*/

#include "libft/glob.h"
#include "glob_climb_tree.h"

//TODO: move this to new file (listutil)
static t_match	*matchctor(char const *path, size_t len)
{
	t_match *new;

	if (!(new = malloc(sizeof(t_match) + len)))
		return (NULL);

	ft_bzero(new, sizeof(t_match));
	ft_memcpy(new->buf, path, len);

	return (new);
}

static void matchdtor(t_match *match)
{
	t_match *prev;

	if (!match)
		return;
	prev = match;
	match = match->next;
	free(prev);
	while (match)
	{
		prev = match;
		match = match->next;
		free(prev);
	}
}

static t_bool add_match_to_list(t_match *match, t_match *match_list, int flags)
{
	(void)match; //TODO
	(void)match_list; //TODO

/*
		if ((flags & GLOB_MARK))
			append_slash_to_each_name();
*/

	return TRUE;
}
//TODO: endmove

static char **handle_brace_expansion(char const *pattern)
{
	//TODO
	(void)pattern;

	return (char **)42;
}

static int tree_climber(char const *dir, char const *pattern, int flags, int depth)
{
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

		if not glob_match(
			'/' + subpats[:depth - len(subpats)].join('/'),
				// re-join pattern from the begin to i
			file
		):
			files.pop(file)

		if not GLOB_PERIOD and GLOB_MAGCHAR and file[0] == '.':
			files.pop(file)

		//TODO: should we reset the GLOB_MAGCHAR flag?

	//no more recursion needed, just return matching files
	if depth == 1:
		return files

	// loop on matching dirs/links
	for(file in files):
		if is_a_dir_or_link(file):
			ret += tree_climber(
				file,
				pattern,
				flags,
				depth - 1
			)

	return ret  //TODO: return mismatch :o
*/
	(void)dir; //TODO
	(void)pattern; //TODO
	(void)depth; //TODO
	(void)flags; //TODO

	return GLOB_SUCCESS;
}

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

	ret = tree_climber(search_start, pattern, flags, depth);
/*
	if GLOB_NOCHECK and not files:
		return pattern
	if GLOB_NOMAGIC and not GLOB_MAGCHAR:
		return pattern
*/
	return ret;
}
