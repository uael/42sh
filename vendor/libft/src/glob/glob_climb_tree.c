/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:23:43 by mc                #+#    #+#             */
/*   Updated: 2018/02/13 14:39:53 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob_climb_tree - glob util function to check recursively a directory tree
*/

#include "libft/glob.h"
#include "glob_climb_tree.h"

int tree_climber(char *search_start, char const *pattern, \
				 int flags, t_match **match_list, int depth); //TODO: ooops

/*
static char **handle_brace_expansion(char const *pattern)
{
	//TODO
	(void)pattern;

	return (char **)42;
}
*/


static int glob_open_dir(DIR **dir, char *search_start, char const *pattern, \
						 int flags)
{
	char	swap;

	swap = *search_start; // '/' or 0
	*search_start = '\0';
	//TODO: are we supposed to check if it's a dir before opendir?
	if (!(*dir = opendir(pattern)))
	{
		*search_start = swap;
		if ((flags & GLOB_ERR))
			return GLOB_ABORTED; //TODO: is it a "read" error?

		//TODO: not sure what to do here
		return GLOB_SUCCESS;
	}
	*search_start = swap;

	return GLOB_SUCCESS;
}
static int glob_close_dir(DIR *dir, int flags)
{
	if (closedir(dir))
	{
		if ((flags & GLOB_ERR))
			return GLOB_ABORTED; //TODO: is it a "read" error?

		//TODO: not sure what to do here
		return GLOB_SUCCESS;
	}

	return GLOB_SUCCESS;
}

static int tree_climber_loop(struct dirent *dirent, char const *pattern, \
							 int flags, t_match **match_list, int depth) //TODO: ooops
{
	int			ret;
	t_match		*match;
	char		*next_slash;

	if ((flags & GLOB_ONLYDIR) && IS_DIR(dirent))
		return GLOB_SUCCESS;

	//TODO: could check depth instead
	if ((next_slash = ft_strchr(pattern + dirent->d_reclen, '/')))
	{
		*next_slash = '\0';
		if (!glob_match(pattern, dirent->d_name, flags))
			return GLOB_SUCCESS;
		*next_slash = '/';
	}
	else if (!glob_match(pattern, dirent->d_name, flags))
		return GLOB_SUCCESS;
	//TODO: should we reset the GLOB_MAGCHAR flag?

	if ((flags & GLOB_PERIOD) && !(flags & GLOB_MAGCHAR) \
			&& *(dirent->d_name) == '.')
		return GLOB_SUCCESS;

	if (!(match = matchctor(dirent->d_name, dirent->d_reclen)))
		return GLOB_NOSPACE;
	add_match_to_list(match, match_list);

	if (IS_DIR(dirent))
	{
		ret = tree_climber(dirent->d_name, pattern,		\
						   flags, match_list, depth - 1); //BOOOOM BABY!
		if (ret != GLOB_SUCCESS)
			return ret;
	}

	return GLOB_SUCCESS;
}

int tree_climber(char *search_start, char const *pattern, \
				 int flags, t_match **match_list, int depth) //TODO: ooops
{
	DIR				*dir;
	struct dirent	*dirent;
	int				ret;

	if (!depth)
		return GLOB_SUCCESS;

	ret = glob_open_dir(&dir, search_start, pattern, flags);
	if (ret != GLOB_SUCCESS)
		return ret;

	while ((dirent = readdir(dir)))
	{
		ret = tree_climber_loop(dirent, pattern, flags, match_list, depth);
		if (ret != GLOB_SUCCESS)
		{
			glob_close_dir(dir, flags);
			return ret;
		}
	}
/*
	//TODO: errno
	if (read_error && (flags & GLOB_ERR))
		return GLOB_ABORTED;
*/

	return glob_close_dir(dir, flags);
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

	search_start = pattern;
	if (depth != 1)
		search_start = pattern;
		while (*search_start != '/')
			search_start++;

	ret = tree_climber((char *)(unsigned long)(search_start), /* const? nop */ \
					   pattern, flags, match_list, depth);
/*
	if GLOB_NOCHECK and not files:
		return pattern
	if GLOB_NOMAGIC and not GLOB_MAGCHAR:
		return pattern
*/
	return ret;
}
