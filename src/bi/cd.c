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

static char	*cd_path(t_sh *self, t_vstr *av, t_bool p)
{
	char	**env;

	if ((av->len == 1 + p || ft_strcmp(av->buf[1 + p], "~") == 0) &&
		(env = sh_getenv(&self->env, "HOME")))
		return (*env + 5);
	if (av->len == 2 + p && ft_strcmp(av->buf[1 + p], "-") == 0 &&
		(env = sh_getenv(&self->env, "OLDPWD")))
		return (*env + 7);
	if (av->len == 2 + p)
		return (av->buf[1 + p]);
	return (NULL);
}

static t_st	cd_test(char *path)
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

static char	*cd_pathreal(char *path, char *buf, char **pwd, t_bool p)
{
	char	prev[PATH_MAX + 1];

	ft_strcpy(prev, path);
	if (!(path = ft_pathabs(path, buf, !p && pwd ? *pwd + 4 : NULL)))
		ft_strcpy(path, prev);
	return (path);
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
	if (!(path = cd_path(self, av, (t_bool)(av->len == 3))))
		return (ft_ret(NOK, "%s: %s\n", "cd", "Environ is empty"));
	if ((st = cd_test(path)) != 0)
		return (st);
	if ((pwd = sh_getenv(&self->env, "PWD")) &&
		ISE(st = sh_setenv(&self->env, "OLDPWD", *pwd + 4)))
		return (st);
	path = cd_pathreal(path, buf, pwd, (t_bool)(av->len == 3));
	if (!(chd = chdir(path)) &&
		ISE(st = sh_setenv(&self->env, "PWD", path)))
		return (st);
	return (chd ? ft_ret(NOK, "%s: %e\n", "cd", errno) : OK);
}
