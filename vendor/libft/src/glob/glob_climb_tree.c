/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:23:43 by mc                #+#    #+#             */
/*   Updated: 2018/02/14 21:47:28 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob_climb_tree - glob util function to check recursively a directory tree
*/

#include "libft/ft_glob.h"
#include "glob_climb_tree.h"

#define DIRNAME_BUF_SIZE 255
char *g_dirname_buf; //TODO: don't

/*
static char **handle_brace_expansion(char const *pattern)
{
	//TODO
	(void)pattern;

	return (char **)42;
}
*/

static int glob_open_dir(DIR **dir, int flags)
{
	if (!(*dir = opendir(g_dirname_buf)))
	{
		if ((flags & GLOBUX_ERR))
			return GLOBUX_ABORTED; //TODO: is it a "read" error?

		/*
		  TODO: not sure what to do here:
				open failed, but we shouldn't stop
				maybe print an error message?
		*/
		return GLOBUX_SUCCESS;
	}

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

static void glob_append_dir_name(char const *pattern)
{
	char		*buf;
	int			depth;

	depth = 0;
	buf = g_dirname_buf;
	while (*buf)
	{
		if (*buf == '/')
			depth++;
		buf++;
	}

	while (depth && pattern++)
		if (*pattern == '/')
			depth--;

	ft_strcpy(buf, pattern);
}

static int tree_climber_loop(struct dirent *dirent, char const *pattern, \
							 int flags, t_match **match_list, int depth) //TODO: ooops
{
	int			ret;
	t_match		*match;

	if ((flags & GLOBUX_ONLYDIR) && IS_DIR(dirent))
		return GLOBUX_SUCCESS;

	//TODO: could check depth instead
	if (depth != 1)
	{
		glob_append_dir_name(pattern);
		if (!glob_match(pattern, dirent->d_name, flags))
			return GLOBUX_SUCCESS;
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
		ret = tree_climber(pattern,	flags, match_list, depth - 1); //BOOOOM BABY!
		if (ret != GLOBUX_SUCCESS)
			return ret;
	}

	return GLOBUX_SUCCESS;
}

int tree_climber(char const *pattern, int flags, t_match **match_list, int depth)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				ret;

	if (!depth)
		return GLOBUX_SUCCESS;

	ret = glob_open_dir(&dir, flags);
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
	//TODO: opti for trivial (no magic) case
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
	char		hopefully_this_variable_wont_used_too_much[DIRNAME_BUF_SIZE];

	g_dirname_buf = hopefully_this_variable_wont_used_too_much;
	ft_bzero(g_dirname_buf, DIRNAME_BUF_SIZE);

	depth = 1;
	slash = pattern;
	while (*slash)
	{
		if (*slash == '/')
			depth++;
		slash++;
	}

/*
	// this should be already caught
	if ((size_t)(slash - pattern) > DIRNAME_BUF_SIZE)
		return GLOBUX_NOSPACE;
*/

	if (depth > MAX_DEPTH)
		return GLOBUX_NOSPACE;


	slash = pattern;
	if (depth != 1)
	{
		while (*slash != '/')
			slash++;
		ft_memcpy(g_dirname_buf, pattern, (size_t)(slash - pattern));
	}
	else
		*g_dirname_buf = *pattern == '/' ? '/' : '.';

	ret = tree_climber(pattern, flags, match_list, depth);
/*
	if GLOBUX_NOCHECK and not files:
		return pattern
	if GLOBUX_NOMAGIC and not GLOBUX_MAGCHAR:
		return pattern
*/
	return ret;
}
