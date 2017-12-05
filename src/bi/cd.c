/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 16:15:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <limits.h>

#include "msh/bi.h"
#include "msh/env.h"

static char	*cd_path(int ac, char **av, char **env, t_bool p)
{
	char *envv;

	if ((ac == 1 + p || ft_strcmp(av[1 + p], "~") == 0) &&
		(envv = ft_getenv(env, "HOME")))
		return (envv);
	if (ac == 2 + p && ft_strcmp(av[1 + p], "-") == 0 &&
		(envv = ft_getenv(env, "OLDPWD")))
		return (envv);
	if (ac == 2 + p)
		return (av[1 + p]);
	return (NULL);
}

static t_st	cd_test(char *path)
{
	struct stat	s;

	if (!*path || lstat(path, &s) < 0 != 0)
		return (ft_retf(NOK, "%s: %e\n", "cd", errno));
	if (!S_ISDIR(s.st_mode) && !S_ISLNK(s.st_mode))
		return (ft_retf(NOK, "%s: %e\n", "cd", ENOTDIR));
	if (!S_ISLNK(s.st_mode) && access(path, R_OK) != 0)
		return (ft_retf(NOK, "%s: %e\n", "cd", errno));
	if (access(path, X_OK) != 0)
		return (ft_retf(NOK, "%s: %e\n", "cd", errno));
	return (OK);
}

static char	*cd_pathreal(char *path, char *buf, char *pwd, t_bool p)
{
	char	prev[PATH_MAX + 1];

	ft_strcpy(prev, path);
	if (!(path = ft_pathabs(path, buf, !p && pwd ? pwd : NULL)))
		ft_strcpy(path, prev);
	return (path);
}

inline int	sh_bi_cd(t_sh *sh, int ac, char **av, char **env)
{
	char	buf[PATH_MAX + 1];
	char	*path;
	char	*pwd;
	int		chd;
	t_st	st;

	if (ac > 3)
		return (ft_retf(NOK, "%s: %e\n", "cd", E2BIG));
	if (ac == 3 && ft_strcmp("-P", av[1]) != 0)
		return (ft_retf(NOK, "%s: %e '%s'\n", "cd", EINVAL, av[1]));
	if (!(path = cd_path(ac, av, env, (t_bool)(ac == 3))))
		return (ft_retf(NOK, "%s: %s\n", "cd", "Environ is empty"));
	if ((st = cd_test(path)) != 0)
		return (st);
	if ((pwd = ft_getenv(env, "PWD")) &&
		ISE(st = sh_setenv(&sh->env, "OLDPWD", pwd)))
		return (st);
	path = cd_pathreal(path, buf, pwd, (t_bool)(ac == 3));
	if (!(chd = chdir(path)) &&
		ISE(st = sh_setenv(&sh->env, "PWD", path)))
		return (st);
	return (chd ? ft_retf(NOK, "%s: %e\n", "cd", errno) : OK);
}
