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

static char	*sh_cd_dir(t_sh *self, t_vstr *av, t_bool p)
{
	char	**env;

	if ((av->len == 1 + p || ft_strcmp(av->buf[1 + p], "~") == 0) &&
		(env = sh_getenv(self, "HOME")))
		return (*env + 5);
	if (av->len == 2 + p && ft_strcmp(av->buf[1 + p], "-") == 0 &&
		(env = sh_getenv(self, "OLDPWD")))
		return (*env + 7);
	if (av->len == 2 + p)
		return (av->buf[1 + p]);
	return (NULL);
}

static t_st	sh_cd_test(char *path)
{
	struct stat	s;

	if (!*path || lstat(path, &s) < 0 != 0)
		return (ft_ret(NOK, "%s: %e\n", "cd", errno));
	if (!S_ISDIR(s.st_mode) && !S_ISLNK(s.st_mode))
		return (ft_ret(NOK, "%s: %e\n", "cd", ENOTDIR));
	if (!S_ISLNK(s.st_mode) && access(path, R_OK) != 0)
		return (ft_ret(NOK, "%s: %e\n", "cd", errno));
	if (access(path, X_OK) != 0)
		return (ft_ret(NOK, "%s: %e\n", "cd", errno));
	return (OK);
}

inline t_st	sh_bi_cd(t_sh *self, t_vstr *av)
{
	char	buf[PATH_MAX + 1];
	char	*path;
	char	**pwd;
	int		chd;
	t_st	st;

	if (av->len > 3)
		return (ft_ret(NOK, "%s: %e\n", "cd", E2BIG));
	if (av->len == 3 && ft_strcmp("-P", av->buf[1]) != 0)
		return (ft_ret(NOK, "%s: %e '%s'\n", "cd", EINVAL, av->buf[1]));
	if (!(path = sh_cd_dir(self, av, (t_bool)(av->len == 3))))
		return (ft_ret(NOK, "%s: %s\n", "cd", "Environ is empty"));
	if ((st = sh_cd_test(ft_strcpy(buf, path))) != 0)
		return (st);
	if ((pwd = sh_getenv(self, "PWD")) &&
		ISE(st = sh_setenv(self, "OLDPWD", *pwd + 4)))
		return (st);
	if (!(chd = chdir(buf)) &&
		ISE(st = sh_setenv(self, "PWD", getcwd(buf, PATH_MAX))))
		return (st);
	return (chd ? ft_ret(NOK, "%s: %e\n", "cd", errno) : OK);
}
