/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_ctor_exe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:43:02 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

#include "libft/exe.h"

static t_st	exe_test(char *exe)
{
	struct stat s;

	if (!*exe || lstat(exe, &s) < 0 || !(s.st_mode & (S_IFREG | S_IXUSR)))
		return (NOK);
	return (OK);
}

static t_st	exe_lookup(char **env, char *exe, char *path, char *buf)
{
	char	*beg;
	char	*sep;
	size_t	len;
	t_st	st;

	if (ST_OK(st = exe_test(ft_strcpy(buf, exe))) || ISE(st))
		return (st);
	if (!(beg = ft_getenv(env, path)))
		return (exe_test(ft_strcat(ft_strcpy(buf, "/bin/"), exe)));
	while ((sep = ft_strchr(beg, ':')) >= 0)
	{
		len = sep ? sep - beg : ft_strlen(beg);
		ft_strncpy(buf, beg, len)[len] = '\0';
		if (ST_OK(st = exe_test(ft_pathcat(buf, exe))) || ISE(st))
			return (st);
		if (!sep)
			break ;
		beg = sep + 1;
	}
	return (NOK);
}

inline t_st ft_job_exe(t_job *self, char *path, char **av, char **env)
{
	t_st	st;
	char	buf[PATH_MAX + 1];

	if (ST_NOK(st = exe_lookup(env, av[0], path, buf)))
		return (st);
	if (access(buf, R_OK) != 0 || access(buf, X_OK) != 0)
		return (ENO);
	if (!(av[0] = ft_strdup(buf)))
		return (ENO);
	FT_INIT(self, t_job);
	self->kind = JOB_EXE;
	self->av = av;
	self->env = env;
	return (OK);
}
