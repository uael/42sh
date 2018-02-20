/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 21:56:00 by mc                #+#    #+#             */
/*   Updated: 2018/02/20 17:20:14 by mcanal           ###   ########.fr       */
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
