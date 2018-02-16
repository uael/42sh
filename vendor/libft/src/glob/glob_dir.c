/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 21:56:00 by mc                #+#    #+#             */
/*   Updated: 2018/02/16 15:33:40 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_climb_tree.h"

int			glob_count_depth(char const *pattern)
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

int			glob_open_dir(DIR **dir, char const *dir_name, int flags)
{
	*dir = opendir(dir_name);
	if (!*dir)
	{
		if ((flags & GLOBUX_ERR))
			return GLOBUX_ABORTED; //TODO: is it a "read" error?

		/*
		  TODO: not sure what to do here:
				open failed, but we shouldn't stop
				maybe print an error message?
		*/
		return GLOBUX_NOBODY_GIVES_A_DAMN;
	}

	return GLOBUX_SUCCESS;
}

int			glob_close_dir(DIR *dir, int flags)
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
		return GLOBUX_NOBODY_GIVES_A_DAMN;
	}

	return GLOBUX_SUCCESS;
}


/*
** Write into PATH_BUF buffer the PREVIOUS_DIR path followed by the NEW_DIR
*/
int			glob_append_dir_name(char *path_buf, char const *prev_dir, \
							 char const *new_dir, size_t new_size)
{
	size_t prev_size;

	prev_size = ft_strlen(prev_dir);
	if (prev_size + new_size + 2 > PATH_MAX)
		return GLOBUX_NOSPACE;

	ft_memcpy(path_buf, prev_dir, prev_size);

	if (*(path_buf + prev_size - 1) != '/')
	{
		*(path_buf + prev_size) = '/';
		ft_memcpy(path_buf + prev_size + 1, new_dir, new_size + 1);
	}
	else
		ft_memcpy(path_buf + prev_size, new_dir, new_size + 1);

	return GLOBUX_SUCCESS;
}



/*
** return the current sub-pattern that should be check at the given depth
** eg: pattern='/?a/?b/?c/?d' depth=2 -> '?c'
**
** the sub-pattern is stored in some buffer, don't worry about it
*/
char const	*glob_get_sub_pattern(char const *pattern, int depth)
{
/* TODO:
   maybe create this buffer before and send the address,
   so it won't stay forever on the stack
*/
	static char	sub_pat_buf[FILE_MAX]; //we'll only need one buffer for all stacks
	char const	*dir_end;
	char const	*pat;
	size_t		len;

	pat = pattern;
	while (*pat)
		pat++;

	while (depth && pat != pattern && pat--)
		if (*pat == '/')
			depth--;

	dir_end = pat;
	while (*dir_end && *dir_end != '/')
		dir_end++;

	len = (size_t)(dir_end - pat);
	if (len + 1 > FILE_MAX)
		return NULL; // this shouldn't happen. ever

	ft_bzero(sub_pat_buf, FILE_MAX);
	ft_memcpy(sub_pat_buf, pat, len);
	if (*dir_end)
		*(sub_pat_buf + len) = '\0';

	return sub_pat_buf;
}
