/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 21:56:00 by mc                #+#    #+#             */
/*   Updated: 2018/02/26 00:58:08 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_util.h"

/*
** Append to PATH_BUF buffer the NEW_FILE file-name
** (and eventually delete any file-name previously added by this function)
**
** assume we'll find a trailing slash in PATH_BUF (cf. glob_store_dir_name())
*/

int			glob_append_file_name(char *path_buf, char const *new_file)
{
	char	*path;
	size_t	new_size;

	new_size = ft_strlen(new_file);
	path = ft_strrchr(path_buf, '/') + 1;
	if ((size_t)(path - path_buf) + new_size + 2 > PATH_MAX)
		return (GLOBUX_NOSPACE);
	ft_memcpy(path, new_file, new_size + 1);
	return (GLOBUX_SUCCESS);
}

/*
** Store into PATH_BUF buffer the PREVIOUS_DIR path followed by the NEW_DIR
**
** delete any previous content of path_buf
** append a trailing slash if there is none
*/

int			glob_store_dir_name(char *path_buf, char const *prev_dir, \
								char	const *new_dir)
{
	size_t	prev_size;
	size_t	new_size;

	prev_size = ft_strlen(prev_dir);
	new_size = ft_strlen(new_dir);
	if (prev_size + new_size + 3 > PATH_MAX)
		return (GLOBUX_NOSPACE);
	ft_memcpy(path_buf, prev_dir, prev_size);
	if (*(path_buf + prev_size - 1) != '/')
	{
		*(path_buf + prev_size) = '/';
		prev_size++;
	}
	ft_memcpy(path_buf + prev_size, new_dir, new_size + 1);
	if (*(path_buf + prev_size + new_size - 1) != '/')
	{
		*(path_buf + prev_size + new_size) = '/';
		*(path_buf + prev_size + new_size + 1) = '\0';
	}
	return (GLOBUX_SUCCESS);
}

/*
** get the folder name from a full path
** eg: path='/a/b/' -> 'b/'
*/

char const	*glob_get_folder_name(char const *path)
{
	size_t		len;
	char const	*pathux;

	len = ft_strlen(path);
	if (len < 3)
		return (path);
	pathux = path + len - 2;
	while (pathux != path && *pathux != '/')
		pathux--;
	if (pathux != path)
		return (pathux + 1);
	return (path);
}

/*
** return the current sub-pattern that should be check at the given depth
** eg: pattern='/?a/?b/?c/?d' depth=2 -> '?c'
**
** the sub-pattern is stored in some buffer, don't worry about it
*/

t_bool		glob_get_sub_pattern(char *sub_pat_buf, char const *pattern, \
								int depth, int flags)
{
	char	const	*dir_end;
	char	const	*pat;
	size_t			len;

	len = ft_strlen(pattern);
	if ((flags & GLOBUX_ONLYDIR))
		len--;
	pat = pattern + len;
	while (depth && pat != pattern && pat--)
		if (*pat == '/')
			depth--;
	if (pat != pattern || *pat == '/')
		pat++;
	dir_end = pat;
	while (*dir_end && *dir_end != '/')
		dir_end++;
	len = (size_t)(dir_end - pat);
	if (len + 1 > NAME_MAX)
		return (FALSE);
	ft_bzero(sub_pat_buf, NAME_MAX);
	ft_memcpy(sub_pat_buf, pat, len);
	if (*dir_end)
		*(sub_pat_buf + len) = '\0';
	return (TRUE);
}

void		remove_last_dir_from_path(char *path_buf)
{
	char	*path;

	path = path_buf + ft_strlen(path_buf) - 2;
	while (path != path_buf && *path != '/')
		path--;
	*(path + 1) = '\0';
}
