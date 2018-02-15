/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 21:56:00 by mc                #+#    #+#             */
/*   Updated: 2018/02/15 15:21:17 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_climb_tree.h"

extern char *g_dirname_buf;

int		glob_count_depth(char const *pattern)
{
	char const	*slash;
	int			depth;

	depth = 1;
	slash = pattern;
	while (*slash)
	{
		if (*slash == '/')
			depth++;
		slash++;
	}

	return depth;
}

int		glob_open_dir(DIR **dir, int flags)
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

int		glob_close_dir(DIR *dir, int flags)
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

int		glob_append_dir_name(char const *pattern)
{
	char		*buf;
	char const	*dir_end;
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

	dir_end = pattern;
	while (*dir_end && *dir_end != '/')
		dir_end++;
	//TODO: opti for trivial (no magic) case

	if ((size_t)(buf - g_dirname_buf + dir_end - pattern) + 1 > DIRNAME_BUF_SIZE)
		return GLOBUX_NOSPACE;

	ft_memcpy(buf, pattern, (size_t)(dir_end - pattern));
	if (*dir_end)
		*(buf + (size_t)(dir_end - pattern)) = '\0';

	return GLOBUX_SUCCESS;
}
