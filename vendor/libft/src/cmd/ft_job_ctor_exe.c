/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_ctor_exe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 15:56:18 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

#include "libft/cmd.h"

static t_bool	exe_test(char *exe)
{
	struct stat s;

	if (!*exe || lstat(exe, &s) < 0 || !(s.st_mode & (S_IFREG | S_IXUSR)))
		return (FALSE);
	return (TRUE);
}

static t_bool	exe_lookup(char **env, char *exe, char *path, char *buf)
{
	char	*beg;
	char	*sep;
	size_t	len;

	if (exe_test(ft_strcpy(buf, exe)))
		return (TRUE);
	if (!(beg = ft_getenv(env, path)))
		return (exe_test(ft_strcat(ft_strcpy(buf, "/bin/"), exe)));
	while (1)
	{
		sep = ft_strchr(beg, ':');
		len = sep ? (size_t)(sep - beg) : ft_strlen(beg);
		ft_strncpy(buf, beg, len)[len] = '\0';
		if (exe_test(ft_pathcat(buf, exe)))
			return (TRUE);
		if (!sep)
			break ;
		beg = sep + 1;
	}
	return (FALSE);
}

inline int		ft_job_cmd(t_job *self, char *path, char **av, char **env)
{
	char	buf[PATH_MAX + 1];

	if (!exe_lookup(env, av[0], path, buf))
		return (NOP);
	if (access(buf, R_OK) != 0 || access(buf, X_OK) != 0)
		return (THROW(WUT));
	av[0] = ft_strdup(buf);
	FT_INIT(self, t_job);
	ft_vec_ctor(&self->dups, sizeof(t_dup2));
	self->kind = JOB_EXE;
	self->av = av;
	self->env = env;
	self->pin = STDIN_FILENO;
	self->pout = STDOUT_FILENO;
	return (YEP);
}
