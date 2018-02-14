/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 21:56:00 by mc                #+#    #+#             */
/*   Updated: 2018/02/14 21:59:17 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_glob.h"
#include "glob_climb_tree.h"

extern char *g_dirname_buf;

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

void	glob_append_dir_name(char const *pattern)
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
