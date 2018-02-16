/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:23:43 by mc                #+#    #+#             */
/*   Updated: 2018/02/16 15:35:53 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob_climb_tree - glob util function to check recursively a directory tree
*/

#include "glob_climb_tree.h"

/*
static char **handle_brace_expansion(char const *pattern)
{
	//TODO
	(void)pattern;

	return (char **)42;
}
*/

static t_bool show_hidden_files(int flags, char pat_start)
{
	return !(flags & GLOBUX_MAGCHAR) || (flags & GLOBUX_PERIOD) || pat_start == '.';
}

static int	glob_check_file(struct dirent *dirent, char const *pattern, \
							 int flags, t_match **match_list, int depth) //TODO: ooops
{
	t_match		*match;
	char const	*sub_pat;

	if ((flags & GLOBUX_ONLYDIR) && !IS_DIR(dirent))
		return GLOBUX_SUCCESS;

	if (!(sub_pat = glob_get_sub_pattern(pattern, depth))) //TODO: do that once per dir
		return GLOBUX_NOSPACE;
	if (!glob_match(sub_pat, dirent->d_name, flags))
		return GLOBUX_SUCCESS;

	if (*(dirent->d_name) == '.' && !show_hidden_files(flags, *pattern))
		return GLOBUX_SUCCESS;

	if (!(match = matchctor(dirent->d_name, dirent->d_reclen)))
		return GLOBUX_NOSPACE;
	add_match_to_list(match, match_list);

	if (IS_DIR(dirent) \
		&& ft_strcmp(dirent->d_name, ".") && ft_strcmp(dirent->d_name, ".."))
		return GLOBUX_BOOM_BABY;

	return GLOBUX_SUCCESS;
}

int			glob_read_dir(char const *pattern, int flags, \
						  t_match **match_list, int depth, char const *dir_name)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				ret;
	char			path_buf[PATH_MAX]; //we'll need a fresh buffer for each call

	if (!depth)
		return GLOBUX_SUCCESS;

	ft_bzero(&path_buf, PATH_MAX);
	if (!dir_name)
	{
		*path_buf = *pattern == '/' ? '/' : '.';
		dir_name = path_buf;
	}

	if (glob_open_dir(&dir, dir_name, flags) == GLOBUX_ABORTED)
		return GLOBUX_ABORTED;
	if (!dir)
		return GLOBUX_SUCCESS;

	while ((dirent = readdir(dir)))
	{
		ret = glob_check_file(dirent, pattern, flags, match_list, depth);
		if (ret == GLOBUX_BOOM_BABY)
		{
			if (glob_append_dir_name(path_buf, dir_name, \
					 dirent->d_name, dirent->d_reclen) != GLOBUX_SUCCESS)
				return GLOBUX_NOSPACE;
			ret = glob_read_dir(pattern, flags, match_list, depth - 1, path_buf);
			if (ret != GLOBUX_SUCCESS)
			{
				glob_close_dir(dir, flags);
				return ret;
			}
		}
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


	if (glob_close_dir(dir, flags) == GLOBUX_ABORTED)
		return GLOBUX_ABORTED;
	return GLOBUX_SUCCESS;
}

int			glob_climb_tree(char const *pattern, t_glob *pglob, t_match **match_list)
{
/*
	handle_flags(GLOBUX_TILDE | GLOBUX_TILDE_CHECK)

	if '{' in pattern and GLOBUX_BRACE:
		patterns[] = handle_brace_expansion(pattern)
			for pat in patterns:
				if not glob_climb_tree(patn flags)
					return false;
*/
	int			depth;
	char const	*magic;
	//TODO: I guess a trailing slashes in pattern fuck everything up

	depth = glob_count_depth(pattern);
	if (depth > MAX_DEPTH)
		return GLOBUX_NOSPACE;

	if ((magic = is_magic(pattern, &(pglob->gl_flags))))
		return glob_read_dir(pattern, pglob->gl_flags, match_list, depth, \
							 magic == pattern ? NULL : magic);

	if ((pglob->gl_flags & GLOBUX_NOMAGIC))
	{
		if (!(*match_list = matchctor(pattern, ft_strlen(pattern))))
			return GLOBUX_NOSPACE;
		return GLOBUX_SUCCESS;
	}

	return glob_read_dir(pattern, pglob->gl_flags, match_list, depth, NULL);
}
