/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 11:46:29 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <limits.h>

#include "msh/bi.h"
#include "msh/env.h"

#define N_CD COLOR_RED COLOR_BOLD "cd: " COLOR_RESET

static char	*cd_path(int ac, char **av, char **env, t_bool p)
{
	char *envv;

	if ((ac == 1 + p || ft_strcmp(av[1 + p], "~") == 0) &&
		(envv = ft_getenv(env, "HOME")))
		return (ft_strdup(envv));
	if (ac == 2 + p && ft_strcmp(av[1 + p], "-") == 0 &&
		(envv = ft_getenv(env, "OLDPWD")))
		return (ft_strdup(envv));
	if (ac == 2 + p)
		return (ft_strdup(av[1 + p]));
	return (NULL);
}

static t_st	cd_test(t_sh *sh, char *path)
{
	struct stat	s;

	if (!*path || lstat(path, &s) < 0 != 0)
		return (sh_bi_retf(sh, NOK, N_CD"%s: %e\n", path, errno));
	if (!S_ISDIR(s.st_mode) && !S_ISLNK(s.st_mode))
		return (sh_bi_retf(sh, NOK, N_CD"%s: %e\n", path, ENOTDIR));
	if (!S_ISLNK(s.st_mode) && access(path, R_OK) != 0)
		return (sh_bi_retf(sh, NOK, N_CD"%s: %e\n", path, errno));
	if (access(path, X_OK) != 0)
		return (sh_bi_retf(sh, NOK, N_CD"%s: %e\n", path, errno));
	return (OK);
}

static int	cd_chdir(t_sh *sh, char *path)
{
	t_st	st;

	if (chdir(path))
	{
		st = sh_bi_retf(sh, NOK, N_CD"%s: %e\n", path, errno);
		free(path);
		return (st);
	}
	st = sh_setenv(&sh->env, "PWD", path);
	free(path);
	return (ISE(st) ? st : OK);
}

inline int	sh_bi_cd(t_sh *sh, int ac, char **av, t_job *out)
{
	char	buf[PATH_MAX + 1];
	char	*path;
	char	*pwd;
	t_st	st;

	(void)out;
	if (ac > 3)
		return (sh_bi_retf(sh, NOK, N_CD"%e\n", E2BIG));
	if (ac == 3 && ft_strcmp("-P", av[1]) != 0)
		return (sh_bi_retf(sh, NOK, N_CD"%e '%s'\n", EINVAL, av[1]));
	if (!(path = cd_path(ac, av, sh->env.buf, (t_bool)(ac == 3))))
		return (sh_bi_retf(sh, NOK, N_CD"%s\n", "Environ is empty"));
	if ((st = cd_test(sh, path)) != 0)
		return (st);
	if ((pwd = ft_getenv(sh->env.buf, "PWD")) &&
		ISE(st = sh_setenv(&sh->env, "OLDPWD", pwd)))
		return (st);
	if (ft_pathabs(path, buf, ac != 3 && pwd ? pwd : NULL))
	{
		free(path);
		path = ft_strdup(buf);
	}
	return (cd_chdir(sh, path));
}
