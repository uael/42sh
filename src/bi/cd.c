/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 18:42:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <limits.h>

#include "msh/bi.h"
#include "msh/env.h"

static char		*msh_cd_dir(t_msh *self, t_vstr *av, t_bool p)
{
	char	**env;

	if ((av->len == 1 + p || ft_strcmp(av->buf[1 + p], "~") == 0) &&
		(env = msh_getenv(self, "HOME")))
		return (*env + 5);
	if (av->len == 2 + p && ft_strcmp(av->buf[1 + p], "-") == 0 &&
		(env = msh_getenv(self, "OLDPWD")))
		return (*env + 7);
	if (av->len == 2 + p)
		return (av->buf[1 + p]);
	return (NULL);
}

static t_ret	msh_cd_test(char *exe, t_bool p)
{
	struct stat	s;
	char		path[PATH_MAX + 1];
	int			i;
	ssize_t		l;

	i = -1;
	while (++i <= 40)
	{
		if (!*exe || lstat(exe, &s) < 0 != 0)
			return (CMD_NOK("cd: No such file or directory"));
		if (!S_ISDIR(s.st_mode) && !S_ISLNK(s.st_mode))
			return (CMD_NOK("cd: Is not a directory"));
		if (access(exe, R_OK) != 0)
			return (CMD_NOK("cd: Permission denied"));
		if (p || !S_ISLNK(s.st_mode) || !(l = readlink(exe, path, PATH_MAX)))
			return (RET_OK);
		path[l] = '\0';
		ft_strcpy(exe, path);
	}
	return (CMD_NOK("cd: Too many symbolic links"));
}

inline t_ret	msh_bi_cd(t_msh *self, t_vstr *av)
{
	char 	buf[PATH_MAX + 1];
	char	*path;
	char	**pwd;
	int		chd;
	t_ret	r;

	if (av->len > 3)
		return (CMD_NOK("cd: Invalid number of arguments provided"));
	if (av->len == 3 && ft_strcmp("-P", av->buf[1]) != 0)
		return (CMD_NOK("cd: Unrecognized option"));
	if (!(path = msh_cd_dir(self, av, (t_bool)(av->len == 3))))
		return (CMD_NOK("cd: Unable to retrieve path"));
	if ((r = msh_cd_test(ft_strcpy(buf, path), (t_bool)(av->len == 3))) != 0)
		return (r);
	if ((pwd = msh_getenv(self, "PWD")) &&
		msh_setenv(self, "OLDPWD", *pwd + 4) == RET_ERR)
		return (RET_ERR);
	if (!(chd = chdir(buf)) && msh_setenv(self, "PWD", getcwd(buf, 4096)) < 0)
		return (RET_ERR);
	return (chd ? CMD_NOK("cd: Cannot change dir") : RET_OK);
}
