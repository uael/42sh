/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:23:43 by mc                #+#    #+#             */
/*   Updated: 2018/02/17 13:52:37 by mc               ###   ########.fr       */
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

	return ((char **)42);
}
*/

static t_bool show_hidden_files(int flags, char pat_start)
{
	return (!(flags & GLOBUX_MAGCHAR) || (flags & GLOBUX_PERIOD) || pat_start == '.');
}

static int	glob_check_file(struct dirent *dirent, char const *sub_pat, \
							int flags, t_match **match_list, int depth, char *path_buf, char const *pattern) //TODO: ooops
{
	t_match		*match;

	if ((flags & GLOBUX_ONLYDIR) && !IS_DIR(dirent))
		return (GLOBUX_SUCCESS);

	if (!glob_match(sub_pat, dirent->d_name, flags))
		return (GLOBUX_SUCCESS);

	if (*(dirent->d_name) == '.' && !show_hidden_files(flags, *sub_pat))
		return (GLOBUX_SUCCESS);

	if (depth == 1)
	{
		if (!ft_memcmp(path_buf, "./", 2) && ft_memcmp(pattern, "./", 2))
			path_buf += 2;
		if (glob_append_file_name(path_buf, dirent->d_name) != GLOBUX_SUCCESS)
			return (GLOBUX_NOSPACE);
		if (!(match = matchctor(path_buf, ft_strlen(path_buf))))
			return (GLOBUX_NOSPACE);
		add_match_to_list(match, match_list);
	}
	else if (IS_DIR(dirent)								\
		&& ft_strcmp(dirent->d_name, ".") && ft_strcmp(dirent->d_name, ".."))
		return (GLOBUX_BOOM_BABY); //TODO: handle links

	return (GLOBUX_SUCCESS);
}

int			glob_read_dir(char const *pattern, int flags, \
						  t_match **match_list, int depth, char const *dir_name)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				ret;
	char			path_buf[PATH_MAX]; //we'll need a fresh buffer for each call
	char const		*sub_pat;

	if (!depth)
		return (GLOBUX_SUCCESS);


	if (!dir_name)
	{
		ft_memcpy(path_buf, *pattern == '/' ? "/" : ".", 2);
		dir_name = path_buf;
	}
	else
		ft_strcpy(path_buf, dir_name);

	if (glob_open_dir(&dir, glob_get_folder_name(dir_name), flags) == GLOBUX_ABORTED)
		return (GLOBUX_ABORTED);
	if (!dir)
		return (GLOBUX_SUCCESS);

	if (!(sub_pat = glob_get_sub_pattern(pattern, depth)))
		return (GLOBUX_NOSPACE);

	while ((dirent = readdir(dir)))
	{
		ret = glob_check_file(dirent, sub_pat, flags, match_list, depth, path_buf, pattern);
		if (ret == GLOBUX_BOOM_BABY)
		{
			if (glob_store_dir_name(path_buf, dir_name, dirent->d_name) != GLOBUX_SUCCESS)
				return (GLOBUX_NOSPACE);

			ret = glob_read_dir(pattern, flags, match_list, depth - 1, path_buf);
			if (ret != GLOBUX_SUCCESS)
			{
				glob_close_dir(dir, flags);
				return (ret);
			}
			if (!(sub_pat = glob_get_sub_pattern(pattern, depth)))
				return (GLOBUX_NOSPACE);
		}
		if (ret != GLOBUX_SUCCESS)
		{
			glob_close_dir(dir, flags);
			return (ret);
		}
	}
/*
	//TODO: errno
	if (read_error && (flags & GLOBUX_ERR))
		return (GLOBUX_ABORTED);
*/


	if (glob_close_dir(dir, flags) == GLOBUX_ABORTED)
		return (GLOBUX_ABORTED);
	return (GLOBUX_SUCCESS);
}

int			glob_climb_tree(char const *pattern, t_glob *pglob, t_match **match_list)
{
/*
	handle_flags(GLOBUX_TILDE | GLOBUX_TILDE_CHECK)

	if '{' in pattern and GLOBUX_BRACE:
		patterns[] = handle_brace_expansion(pattern)
			for pat in patterns:
				if not glob_climb_tree(patn flags)
					return (false);
*/
	int			depth;
	char const	*magic;
	//TODO: I guess a trailing slashes in pattern fuck everything up

	depth = glob_count_depth(pattern);
	if (depth > MAX_DEPTH)
		return (GLOBUX_NOSPACE);

	if ((magic = is_magic(pattern, &(pglob->gl_flags))))
		return glob_read_dir(pattern, pglob->gl_flags, match_list, depth, \
							 magic == pattern ? NULL : magic);

	if ((pglob->gl_flags & GLOBUX_NOMAGIC))
	{
		if (!(*match_list = matchctor(pattern, ft_strlen(pattern))))
			return (GLOBUX_NOSPACE);
		return (GLOBUX_SUCCESS);
	}

	return (glob_read_dir(pattern, pglob->gl_flags, match_list, depth, NULL));
}
