/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:23:43 by mc                #+#    #+#             */
/*   Updated: 2018/02/14 15:21:59 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob_climb_tree - glob util function to check recursively a directory tree
*/

#include "libft/ft_glob.h"
#include "glob_climb_tree.h"

int tree_climber(char *slash, char const *pattern, \
				 int flags, t_match **match_list, int depth); //TODO: ooops

/*
static char **handle_brace_expansion(char const *pattern)
{
	//TODO
	(void)pattern;

	return (char **)42;
}
*/


static int glob_open_dir(DIR **dir, char *slash, char const *pattern, \
						 int flags)
{
	char	swap;

	swap = *slash; // '/' or 0
	*slash = '\0';
	//TODO: are we supposed to check if it's a dir before opendir?
	if (!(*dir = opendir(pattern)))
	{
		*slash = swap;
		if ((flags & GLOBUX_ERR))
			return GLOBUX_ABORTED; //TODO: is it a "read" error?

		/*
		  TODO: not sure what to do here:
				open failed, but we shouldn't stop
				maybe print an error message?
		*/
		return GLOBUX_SUCCESS;
	}
	*slash = swap;

	return GLOBUX_SUCCESS;
}

static int glob_close_dir(DIR *dir, int flags)
{
	if (closedir(dir))
	{
		if ((flags & GLOBUX_ERR))
			return GLOBUX_ABORTED; //TODO: is it a "read" error?

		/*
		  TODO: not sure what to do here:
				close failed, but we shouldn't stop
				maybe print an error message?
		*/
		return GLOBUX_SUCCESS;
	}

	return GLOBUX_SUCCESS;
}

static int tree_climber_loop(struct dirent *dirent, char const *pattern, \
							 int flags, t_match **match_list, int depth) //TODO: ooops
{
	int			ret;
	t_match		*match;
	char		*next_slash;

	if ((flags & GLOBUX_ONLYDIR) && IS_DIR(dirent))
		return GLOBUX_SUCCESS;

	//TODO: could check depth instead
	if ((next_slash = ft_strchr(pattern + dirent->d_reclen, '/')))
	{
		*next_slash = '\0';
		if (!glob_match(pattern, dirent->d_name, flags))
			return GLOBUX_SUCCESS;
		*next_slash = '/';
	}
	else if (!glob_match(pattern, dirent->d_name, flags))
		return GLOBUX_SUCCESS;
	//TODO: should we reset the GLOBUX_MAGCHAR flag?

	if ((flags & GLOBUX_PERIOD) && !(flags & GLOBUX_MAGCHAR) \
			&& *(dirent->d_name) == '.')
		return GLOBUX_SUCCESS;

	if (!(match = matchctor(dirent->d_name, dirent->d_reclen)))
		return GLOBUX_NOSPACE;
	add_match_to_list(match, match_list);

	if (IS_DIR(dirent))
	{
		ret = tree_climber(dirent->d_name, pattern,		\
						   flags, match_list, depth - 1); //BOOOOM BABY!
		if (ret != GLOBUX_SUCCESS)
			return ret;
	}

	return GLOBUX_SUCCESS;
}

int tree_climber(char *slash, char const *pattern, \
				 int flags, t_match **match_list, int depth) //TODO: ooops
{
	DIR				*dir;
	struct dirent	*dirent;
	int				ret;

	if (!depth)
		return GLOBUX_SUCCESS;

	ret = glob_open_dir(&dir, slash, pattern, flags);
	if (ret != GLOBUX_SUCCESS)
		return ret;

	while ((dirent = readdir(dir)))
	{
		ret = tree_climber_loop(dirent, pattern, flags, match_list, depth);
		if (ret != GLOBUX_SUCCESS)
		{
			glob_close_dir(dir, flags);
			return ret;
		}
	}
/*
	//TODO: errno
	if (read_error && (flags & GLOBUX_ERR))
		return GLOBUX_ABORTED;
*/

	return glob_close_dir(dir, flags);
}

//TODO: test
int glob_climb_tree(char const *pattern, int flags, t_match **match_list)
{
	//TODO: flags: we might want to pass the whole t_glob struct instead
/*
	handle_flags(GLOBUX_TILDE | GLOBUX_TILDE_CHECK)

	if '{' in pattern and GLOBUX_BRACE:
		patterns[] = handle_brace_expansion(pattern)
			for pat in patterns:
				if not glob_climb_tree(patn flags)
					return false;
*/
	char const	*slash;
	int			depth;
	int			ret;

	depth = 1;
	slash = pattern;
	while (*slash)
	{
		if (*slash == '/')
			depth++;
		slash++;
	}

	if (depth > MAX_DEPTH)
		return GLOBUX_NOSPACE;

	slash = pattern;
	if (depth != 1)
		while (*slash != '/')
			slash++;

	/* if (*pattern == '/') */


	ret = tree_climber((char *)(unsigned long)(slash), /* const? nop */ \
					   pattern, flags, match_list, depth);
/*
	if GLOBUX_NOCHECK and not files:
		return pattern
	if GLOBUX_NOMAGIC and not GLOBUX_MAGCHAR:
		return pattern
*/
	return ret;
}
