/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:23:43 by mc                #+#    #+#             */
/*   Updated: 2018/02/22 12:16:30 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob_climb_tree - glob util function to check recursively a directory tree
*/

#include "glob_climb_tree.h"

static int	show_hidden_files(int flags, char pat_start)
{
	return (!(flags & GLOBUX_MAGCHAR) || (flags & GLOBUX_PERIOD) || pat_start == '.');
}

static void	remove_last_dir_from_path(char *path_buf)
{
	char	*path;

	path = path_buf + ft_strlen(path_buf) - 2;
	while (path != path_buf && *path != '/')
		path--;
	*(path + 1) = '\0';
}

static int	glob_check_file(t_glob_env *glob_env, struct dirent *dirent, \
							int depth, char *path_buf)
{
	t_match		*match;

	if ((*(glob_env->flags) & GLOBUX_ONLYDIR) && !IS_DIR(dirent))
		return (GLOBUX_SUCCESS);

	if (!glob_match(glob_env->sub_pat_buf, dirent->d_name, *(glob_env->flags)))
		return (GLOBUX_SUCCESS);

	if (*(dirent->d_name) == '.' \
		&& !show_hidden_files(*(glob_env->flags), *glob_env->sub_pat_buf))
		return (GLOBUX_SUCCESS);

	if (depth == 1)
	{
		if (glob_append_file_name(path_buf, dirent->d_name, \
									*(glob_env->flags)) != GLOBUX_SUCCESS)
			return (GLOBUX_NOSPACE);
		if (!ft_memcmp(path_buf, "./", 2) && ft_memcmp(glob_env->pattern, "./", 2))
			path_buf += 2;
		if (!(match = matchctor(path_buf, ft_strlen(path_buf))))
			return (GLOBUX_NOSPACE);
		add_match_to_list(match, &glob_env->match_list);
	}
	else if (IS_DIR(dirent)								\
             && (ft_strcmp(dirent->d_name, ".") || !ft_strcmp(glob_env->sub_pat_buf, ".")) \
             && (ft_strcmp(dirent->d_name, "..") || !ft_strcmp(glob_env->sub_pat_buf, "..")))
		return (GLOBUX_BOOM_BABY); //TODO: handle links

	return (GLOBUX_SUCCESS);
}

int			glob_read_dir(t_glob_env *glob_env, \
							int depth, char const *dir_name)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				ret;
	char			path_buf[PATH_MAX]; //we'll need a fresh buffer for each call

	if (!depth)
		return (GLOBUX_SUCCESS);

	if (!dir_name)
	{
		*glob_env->pattern == '/' ? ft_memcpy(path_buf, "/", 2) : ft_memcpy(path_buf, "./", 3);
		dir_name = path_buf;
	}
	else
		ft_strcpy(path_buf, dir_name);

	if (glob_open_dir(&dir, dir_name, *(glob_env->flags)) == GLOBUX_ABORTED)
		return (GLOBUX_ABORTED);
	if (!dir && glob_open_dir(&dir, glob_get_folder_name(dir_name), *(glob_env->flags)))
		return (GLOBUX_SUCCESS);

	if (!glob_get_sub_pattern(glob_env->sub_pat_buf, glob_env->pattern, depth))
		return (GLOBUX_NOSPACE);

	while ((dirent = readdir(dir)))
	{
		ret = glob_check_file(glob_env, dirent, depth, path_buf);
		if (ret == GLOBUX_BOOM_BABY)
		{
			if (glob_store_dir_name(path_buf, dir_name, dirent->d_name) != GLOBUX_SUCCESS)
				return (GLOBUX_NOSPACE);

			ret = glob_read_dir(glob_env, depth - 1, path_buf);
			remove_last_dir_from_path(path_buf);
			if (ret != GLOBUX_SUCCESS)
			{
				glob_close_dir(dir, *(glob_env->flags));
				return (ret);
			}
			if (!glob_get_sub_pattern(glob_env->sub_pat_buf, glob_env->pattern, depth))
				return (GLOBUX_NOSPACE);
		}
		if (ret != GLOBUX_SUCCESS)
		{
			glob_close_dir(dir, *(glob_env->flags));
			return (ret);
		}
	}
/*
//TODO: errno
if (read_error && (*(glob_env->flags) & GLOBUX_ERR))
return (GLOBUX_ABORTED);
*/

	if (glob_close_dir(dir, *(glob_env->flags)) == GLOBUX_ABORTED)
		return (GLOBUX_ABORTED);
	return (GLOBUX_SUCCESS);
}

int			glob_climb_tree(t_glob_env *glob_env)
{
	int			depth;
	char const	*magic;
	/* handle_flags(GLOBUX_TILDE | GLOBUX_TILDE_CHECK | GLOBUX_BRACE) */
	//TODO: I guess a trailing slashes in pattern fuck everything up

	depth = glob_count_depth(glob_env->pattern);
	if ((magic = is_magic(glob_env->magic_buf, \
							glob_env->pattern, glob_env->flags)))
	{
		if (magic != glob_env->pattern)
			depth = 1 + \
				glob_count_depth(glob_env->pattern) - glob_count_depth(magic); //maths!
		if (depth > MAX_DEPTH || depth < 1)
			return (GLOBUX_NOSPACE);
		return glob_read_dir(glob_env, depth, \
							magic == glob_env->pattern ? NULL : magic);
	}

	if ((*(glob_env->flags) & GLOBUX_NOMAGIC) \
		|| !ft_strcmp("/", glob_env->pattern)) //shit happens
	{
		if (!(glob_env->match_list = matchctor(glob_env->pattern, \
												ft_strlen(glob_env->pattern))))
			return (GLOBUX_NOSPACE);
		return (GLOBUX_SUCCESS);
	}

	if (depth > MAX_DEPTH)
		return (GLOBUX_NOSPACE);
	return (glob_read_dir(glob_env, depth, NULL));
}
