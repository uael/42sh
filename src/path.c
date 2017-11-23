/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 15:19:55 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

inline t_ret	msh_path_lookup(t_msh *self, char *file, int mode, char **ex)
{
	char		**path;
	char		*beg;
	char		*chr;
	char		*cp;
	struct stat	s;

	if (*file == '/' || !(path = msh_getenv(self, "PATH")))
		return (*file == '/' ? !(*ex = ft_strdup(file)) : RET_NOK);
	beg = *path + 5;
	while ((chr = ft_strchr(beg, ':')))
	{
		if (!(*ex = malloc((chr - beg + 1) * sizeof(char))))
			return (RET_ERR);
		((char *)ft_memcpy(*ex, beg, chr - beg))[chr - beg] = '\0';
		if (!ft_strbegw(file, *ex, '\0') && (cp = ft_pathjoin(*ex, file)))
		{
			free(*ex);
			*ex = cp;
		}
		if (lstat(*ex, &s) == 0 && (s.st_mode & mode))
			return (RET_OK);
		free(*ex);
		beg = chr + 1;
	}
	return (RET_NOK);
}
