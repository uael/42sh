/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 14:57:48 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>

#include "msh.h"

static inline char	*msh_cwd(t_msh *self)
{
	size_t	l;
	char	cwd[4096 + 1];
	char	*path;
	char	**home;
	char	*h;

	path = getcwd(cwd, 4096);
	if (!path || !(home = msh_getenv(self, "HOME")))
		return (NULL);
	h = *home + 5;
	if (!ft_strbegw(h, path, '\0'))
		return (path);
	if (path[l = ft_strlen(h)] != '\0')
		ft_memmove(path + 1, path + l, (l - 1) * sizeof(char));
	ft_strcpy(path, "~");
	return (path);
}

inline t_ret		msh_prompt(t_msh *self, char *prompt)
{
	char	*cwd;

	if (!(cwd = msh_cwd(self)))
		return (RET_ERR);
	ft_puts(1, cwd);
	ft_puts(1, prompt);
	return (RET_OK);
}
