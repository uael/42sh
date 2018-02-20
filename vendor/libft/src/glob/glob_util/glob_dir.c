/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 21:56:00 by mc                #+#    #+#             */
/*   Updated: 2018/02/20 12:52:43 by mc               ###   ########.fr       */
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
			return (GLOBUX_ABORTED); //TODO: is it a "read" error?

		/*
		  TODO: not sure what to do here:
				open failed, but we shouldn't stop
				maybe print an error message?
		*/
		return (GLOBUX_NOBODY_GIVES_A_DAMN);
	}

	return (GLOBUX_SUCCESS);
}

int			glob_close_dir(DIR *dir, int flags)
{
	if (closedir(dir))
	{
		if ((flags & GLOBUX_ERR))
			return (GLOBUX_ABORTED); //TODO: is it a "read" error?

		/*
		  TODO: not sure what to do here:
				close failed, but we shouldn't stop
				maybe print an error message?
		*/
		return (GLOBUX_NOBODY_GIVES_A_DAMN);
	}

	return (GLOBUX_SUCCESS);
}
