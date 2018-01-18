/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <limits.h>

#include "ush/bi.h"

#define N_CD COLOR_RED COLOR_BOLD "cd: " COLOR_RESET

static char		*cd_path(int ac, char **av, char **env, t_bool p)
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

static int		cd_test(char *path)
{
	struct stat	s;

	if (!*path || lstat(path, &s) != 0)
		return (ft_putf(1, N_CD"%s: %e\n", path, errno));
	if (!S_ISDIR(s.st_mode) && !S_ISLNK(s.st_mode))
		return (ft_putf(1, N_CD"%s: %e\n", path, ENOTDIR));
	if (!S_ISLNK(s.st_mode) && access(path, R_OK) != 0)
		return (ft_putf(1, N_CD"%s: %e\n", path, errno));
	if (access(path, X_OK) != 0)
		return (ft_putf(1, N_CD"%s: %e\n", path, errno));
	return (YEP);
}

static int		cd_chdir(char *path, char **env, int ac, char **av)
{
	int	st;

	if (chdir(path))
	{
		st = ft_putf(1, N_CD"%s: %e\n", path, errno);
		free(path);
		return (st);
	}
	sh_bisetenv(ac, av, env);
	free(path);
	return (YEP);
}

inline int		sh_bi_cd(int ac, char **av, char **env)
{
    char	buf[PATH_MAX + 1];
	char	*path;
	char	*pwd;

    if (ac > 3)
		return (ft_putf(1, N_CD"%e\n", E2BIG));
	if (ac == 3 && ft_strcmp("-P", av[1]) != 0)
		return (ft_putf(1, N_CD"%e '%s'\n", EINVAL, av[1]));
	if (!(path = cd_path(ac, av, env, (t_bool)(ac == 3))))
		return (ft_putf(1, N_CD"%s\n", "Environ is empty"));
	if (cd_test(path))
		return (NOP);
	if ((pwd = ft_getenv(env, "PWD")))
		sh_bisetenv(ac, av, env);
	if (ft_pathabs(path, buf, ac != 3 && pwd ? pwd : NULL))
	{
		free(path);
		path = ft_strdup(buf);
	}
	return (cd_chdir(path, env, ac, av));
}