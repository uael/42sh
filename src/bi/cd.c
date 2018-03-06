/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi/cd.c                                            :+:      :+:    :+:   */
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
#include "ush/env.h"

#define CD "cd: "
#define USAGE "cd: usage: cd [-L|-P] [dir]\n"

static int		g_hyphen = 0;

static char		*cd_path(int ac, char **av, char **env, t_bool p)
{
	char *envv;

	g_hyphen = 0;
	if ((ac == 1 + p) && (envv = ft_getenv(env, "HOME")))
		return (ft_strdup(envv));
	if (ac == 2 + p)
	{
		if (ft_strcmp(av[1 + p], "-") == 0 && (envv = ft_getenv(env, "OLDPWD")))
		{
			g_hyphen = 1;
			return (ft_strdup(envv));
		}
		else if (ft_strcmp(av[1 + p], "-L") == 0 &&
			(envv = ft_getenv(env, "HOME")))
			return (ft_strdup(envv));
		else if (ft_strcmp(av[1 + p], "-P") == 0 &&
			(envv = ft_getenv(env, "HOME")))
			return (ft_strdup(envv));
		else
			return (ft_strdup(av[1 + p]));
	}
	return (NULL);
}

static int		cd_test(char *path)
{
	struct stat	s;

	if (!*path || lstat(path, &s) != 0)
		return (ft_retf(NOP, CD"%s: %e\n", path, errno));
	if (!S_ISDIR(s.st_mode) && !S_ISLNK(s.st_mode))
		return (ft_retf(NOP, CD"%s: %e\n", path, ENOTDIR));
	if (!S_ISLNK(s.st_mode) && access(path, R_OK) != 0)
		return (ft_retf(NOP, CD"%s: %e\n", path, errno));
	if (access(path, X_OK) != 0)
		return (ft_retf(NOP, CD"%s: %e\n", path, errno));
	return (YEP);
}

static int		cd_chdir(char *real, char **envv)
{
	int		st;
	char	*pwd;

	if (chdir(real))
	{
		st = ft_retf(NOP, CD"%s: %e\n", real, errno);
		free(real);
		return (st);
	}
	if (g_hyphen)
		ft_putl(STDOUT_FILENO, real);
	if ((pwd = ft_getenv(envv, "PWD")))
		sh_setenv("OLDPWD", pwd);
	sh_setenv("PWD", real);
	free(real);
	return (YEP);
}

inline int		sh_bicd(int ac, char **av, char **env)
{
	char	buf[PATH_MAX + 1];
	char	*path;
	char	*pwd;
	t_bool	p;

	p = (t_bool)(ac == 3 && ft_strcmp("-P", av[1]) == 0);
	if (ac > 3)
		return (ft_retf(NOP, CD"%e\n", E2BIG));
	if ((ac == 3 || (ac > 1 && *av[1] == '-' && *(av[1] + 1))) && !p &&
		ft_strcmp("-L", av[1]))
		return (ft_retf(NOP, CD"-%c: invalid option\n"USAGE, *(av[1] + 1)));
	if (!(path = cd_path(ac, av, env, (t_bool)(ac == 3))))
		return (ft_retf(NOP, CD"%s\n", "Environ is empty"));
	if (cd_test(path))
	{
		free(path);
		return (NOP);
	}
	pwd = ft_getenv(env, "PWD");
	if (ft_pathabs(path, buf, !p && pwd ? pwd : NULL))
	{
		free(path);
		path = ft_strdup(buf);
	}
	return (cd_chdir(path, env));
}
