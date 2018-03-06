/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_sanitize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:38:00 by mc                #+#    #+#             */
/*   Updated: 2018/03/04 18:17:40 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_util.h"

/*
** remove all the ugly stuffs from patterns (mostly extraneous slashes)
** note: dst and src might overlap
*/

char						*glob_sanitize_pattern(char *dst, const char *src)
{
	char	tmp_buf[PATH_MAX];
	char	*b;

	b = tmp_buf;
	while (*src && (size_t)(b - tmp_buf) < PATH_MAX)
	{
		if (ft_memcmp(src, "//", 2))
			*b++ = *src;
		src++;
	}
	*b = '\0';
	return (ft_strcpy(dst, tmp_buf));
}
