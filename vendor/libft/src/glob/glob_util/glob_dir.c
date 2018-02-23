/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 21:56:00 by mc                #+#    #+#             */
/*   Updated: 2018/02/23 17:17:42 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_util.h"

int			glob_count_depth(char const *pattern)
{
	int			depth;

	depth = 1;
	if (*pattern == '/')
		pattern++;
	while (*pattern)
	{
		if (*pattern == '/')
			depth++;
		pattern++;
	}
	return (depth);
}

int			glob_open_dir(DIR **dir, char const *dir_name, int flags)
{
	*dir = opendir(dir_name);
	if (!*dir)
	{
		if ((flags & GLOBUX_ERR))
			return (GLOBUX_ABORTED);
		return (GLOBUX_NOBODY_GIVES_A_DAMN);
	}
	return (GLOBUX_SUCCESS);
}

int			glob_close_dir(DIR *dir, int flags)
{
	if (closedir(dir))
	{
		if ((flags & GLOBUX_ERR))
			return (GLOBUX_ABORTED);
		return (GLOBUX_NOBODY_GIVES_A_DAMN);
	}
	return (GLOBUX_SUCCESS);
}

void		glob_init_dir_name(char const **dirname, char *path_buf, \
							char const *pattern)
{
	if (!*dirname)
	{
		ft_memcpy(path_buf, *pattern == '/' ? "/\0" : "./", 3);
		*dirname = path_buf;
	}
	else
		ft_strcpy(path_buf, *dirname);
}

int			glob_actually_open_some_folder(t_glob_env *e, char const *dirname, \
										int depth, DIR **dir)
{
	if (glob_open_dir(dir, dirname, *(e->flags)) && !*dir \
		&& glob_open_dir(dir, glob_get_folder_name(dirname), *(e->flags)))
		return (GLOBUX_SUCCESS + 1);
	if (!glob_get_sub_pattern(e->sub_pat_buf, e->pattern, depth, *(e->flags)))
		return (GLOBUX_NOSPACE + 1);
	return (GLOBUX_SUCCESS);
}
