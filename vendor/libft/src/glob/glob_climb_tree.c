/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:23:43 by mc                #+#    #+#             */
/*   Updated: 2018/02/23 20:41:54 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob_climb_tree - glob util function to check recursively a directory tree
*/

#include "glob_climb_tree.h"

static void	remove_last_dir_from_path(char *path_buf)
{
	char	*path;

	path = path_buf + ft_strlen(path_buf) - 2;
	while (path != path_buf && *path != '/')
		path--;
	*(path + 1) = '\0';
}

static int	glob_pre_check_file(t_glob_env *e, struct dirent *d)
{
	if ((*(e->flags) & GLOBUX_ONLYDIR) && !IS_DIR(d))
		return (GLOBUX_SUCCESS);
	if (!glob_match(e->sub_pat_buf, d->d_name, *(e->flags)))
		return (GLOBUX_SUCCESS);
	if (*(d->d_name) == '.' && !show_hidden_files(*(e->flags), *e->sub_pat_buf))
		return (GLOBUX_SUCCESS);
	return (42);
}

static int	glob_check_file(t_glob_env *e, struct dirent *d, \
							int depth, char *path_buf)
{
	t_match		*match;
	size_t		len;

	if (!glob_pre_check_file(e, d))
		return (GLOBUX_SUCCESS);
	if (depth == 1)
	{
		if (glob_append_file_name(path_buf, d->d_name) != GLOBUX_SUCCESS)
			return (GLOBUX_NOSPACE);
		if (!ft_memcmp(path_buf, "./", 2) && ft_memcmp(e->pattern, "./", 2))
			path_buf += 2;
		if ((*(e->flags) & (GLOBUX_MARK | GLOBUX_ONLYDIR)) \
			&& (len = ft_strlen(path_buf)) && *(path_buf + len - 1) != '/')
			ft_memcpy(path_buf + len, "/", 2);
		if (!(match = matchctor(path_buf, ft_strlen(path_buf))))
			return (GLOBUX_NOSPACE);
		add_match_to_list(match, &e->match_list);
		if (*(e->flags) & (GLOBUX_MARK | GLOBUX_ONLYDIR))
			*(path_buf + len) = '\0';
	}
	else if (IS_DIR(d) \
			&& (ft_strcmp(d->d_name, ".") || !ft_strcmp(e->sub_pat_buf, ".")) \
			&& (ft_strcmp(d->d_name, "..") || !ft_strcmp(e->sub_pat_buf, "..")))
		return (GLOBUX_BOOM_BABY);
	return (GLOBUX_SUCCESS);
}

int			glob_read_dir(t_glob_env *e, int depth, char const *dirname)
{
	DIR				*dir;
	struct dirent	*d;
	int				ret;
	char			path_buf[PATH_MAX];

	glob_init_dir_name(&dirname, path_buf, e->pattern);
	if ((ret = glob_actually_open_some_folder(e, dirname, depth, &dir)))
		return (ret - 1);
	while ((d = readdir(dir)))
		if ((ret = glob_check_file(e, d, depth, path_buf)) \
			== GLOBUX_BOOM_BABY && depth > 1)
		{
			if (glob_store_dir_name(path_buf, dirname, d->d_name))
				return (GLOBUX_NOSPACE);
			if (glob_read_dir(e, depth - 1, path_buf))
				return (glob_close_dir(dir, *(e->flags)) | GLOBUX_ABORTED);
			remove_last_dir_from_path(path_buf);
			if (!glob_get_sub_pattern(e->sub_pat_buf, e->pattern, depth, \
									*(e->flags)))
				return (GLOBUX_NOSPACE);
		}
		else if (ret != GLOBUX_SUCCESS)
			return (glob_close_dir(dir, *(e->flags)) | GLOBUX_ABORTED);
	return (glob_close_dir(dir, *(e->flags)) == GLOBUX_ABORTED ? \
			GLOBUX_ABORTED : GLOBUX_SUCCESS);
}

int			glob_climb_tree(t_glob_env *e)
{
	int			depth;
	char const	*magic;

	if ((depth = glob_brace(e)))
		return (depth > 0 ? depth : GLOBUX_SUCCESS);
	depth = glob_count_depth(e->pattern);
	depth -= show_files(e->flags, e->pattern) ? 0 : 1;
	if ((magic = is_magic(e->magic_buf, e->pattern, e->flags)))
	{
		if (magic != e->pattern)
		{
			depth = 1 + glob_count_depth(e->pattern) - glob_count_depth(magic);
			depth -= show_files(e->flags, e->pattern) ? 0 : 1;
		}
		if (depth > MAX_DEPTH || depth < 1)
			return (GLOBUX_NOSPACE);
		return (glob_read_dir(e, depth, magic == e->pattern ? NULL : magic));
	}
	if ((*(e->flags) & GLOBUX_NOMAGIC) \
		|| !ft_strcmp("/", e->pattern) || !ft_strcmp("./", e->pattern))
	{
		return ((e->match_list = matchctor(e->pattern, \
			ft_strlen(e->pattern))) ? GLOBUX_SUCCESS : GLOBUX_NOSPACE);
	}
	return (depth > MAX_DEPTH ? GLOBUX_NOSPACE : glob_read_dir(e, depth, NULL));
}
