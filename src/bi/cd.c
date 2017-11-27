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

#include "msh/bi.h"
#include "msh/env.h"

static char		*msh_cd_dir(t_msh *self, t_vstr *av)
{
	char	**env;

	if ((av->len == 1 || ft_strcmp(av->buf[1], "~") == 0) &&
		(env = msh_getenv(self, "HOME")))
		return (ft_strdup(*env + 5));
	if (av->len == 2 && ft_strcmp(av->buf[1], "-") == 0 &&
		(env = msh_getenv(self, "OLDPWD")))
		return (ft_strdup(*env + 7));
	if (av->len == 2)
		return (ft_pathresolve(av->buf[1]));
	return (NULL);
}

inline t_ret	msh_bi_cd(t_msh *self, t_vstr *av)
{
	char		*path;
	char		*cp;
	char		**pwd;
	int			chd;
	struct stat	s;

	if (av->len > 2)
		return (CMD_NOK("cd: Invalid number of arguments provided"));
	if (!(path = msh_cd_dir(self, av)) && av->len == 1)
		return (CMD_NOK("cd: Unable to retrieve path from env"));
	if ((pwd = msh_getenv(self, "PWD")) &&
		msh_setenv(self, "OLDPWD", *pwd + 4) == RET_ERR)
		return (RET_ERR);
	if (lstat(path, &s) < 0 || access(path, F_OK) != 0)
		return (CMD_NOK("cd: No such file or directory"));
	else if (!S_ISDIR(s.st_mode) && !S_ISLNK(s.st_mode))
		return (CMD_NOK("cd: Is not a directory"));
	else if (access(path, X_OK) != 0)
		return (CMD_NOK("cd: Permission denied"));
	if (!(cp = ft_strdup(path)))
		return (RET_ERR);
	(chd = chdir(path)) ? RET_OK : msh_setenv(self, "PWD", cp);
	free(cp);
	free(path);
	return (chd ? CMD_NOK("cd: Cannot change dir") : RET_OK);
}
