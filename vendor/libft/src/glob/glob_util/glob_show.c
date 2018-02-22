/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_show.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mc.maxcanal@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 21:20:20 by mcanal            #+#    #+#             */
/*   Updated: 2018/02/22 21:21:30 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_util.h"

int	show_hidden_files(int flags, char pat_start)
{
	return (!(flags & GLOBUX_MAGCHAR) \
			|| (flags & GLOBUX_PERIOD) \
			|| pat_start == '.');
}

int	show_files(int *flags, char const *pattern)
{
	if (*pattern && *(pattern + 1) \
		&& *(pattern + ft_strlen(pattern) - 1) == '/')
	{
		*flags |= GLOBUX_ONLYDIR;
		return (FALSE);
	}
	return (TRUE);
}
