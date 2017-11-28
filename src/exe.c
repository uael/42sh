/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 18:11:04 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <limits.h>

#include "msh.h"

inline t_st		msh_exe_av(t_msh *self, t_vstr *av, char *exe)
{
	t_tok *end;

	if (av)
		ft_vstr_ctor(av);
	if (av && !ft_vstr_pushc(av, exe))
		return (ENO);
	while ((end = msh_peek(self)) && end->id)
	{
		if (end->id == MSH_TOK_WORD && av &&
			!ft_vstr_pushc(av, ft_tok_ident(end)->buf))
			return (ENO);
		else if (end->id != MSH_TOK_WORD && !ft_strchr(" \t", end->id))
			break ;
		msh_next(self, NULL);
	}
	if (av && !ft_vstr_grow(av, 1))
		return (ENO);
	if (av)
		FT_INIT(ft_vstr_end(av), char *);
	return (OK);
}

static t_st		msh_exe_test(char *exe, int mode)
{
	struct stat	s;
	char		path[PATH_MAX + 1];
	int			i;
	ssize_t		l;

	i = -1;
	while (++i <= 40)
	{
		if (!*exe || lstat(exe, &s) < 0 || !(s.st_mode & mode))
			return (NOK);
		if (!S_ISLNK(s.st_mode) || !(l = readlink(exe, path, PATH_MAX)))
			return (OK);
		path[l] = '\0';
		ft_strcpy(exe, path);
	}
	return (ERR(errno = ELOOP));
}

inline t_st		msh_exe_lookup(t_msh *self, char *f, int mode, char exe[])
{
	char	**path;
	char	*beg;
	char	*sep;
	size_t	len;
	t_st	st;

	if (ST_NOK(st = msh_exe_test(ft_strcpy(exe, f), mode)))
		return (st);
	if (!(path = msh_getenv(self, "PATH")))
		return (msh_exe_test(ft_strcat(ft_strcpy(exe, "/bin/"), f), mode));
	beg = *path + 5;
	while ((sep = ft_strchr(beg, ':')) >= 0)
	{
		len = sep ? sep - beg : ft_strlen(beg);
		ft_strncpy(exe, beg, len)[len] = '\0';
		ft_pathcat(exe, f);
		if (ST_NOK(st = msh_exe_test(exe, mode)))
			return (st);
		if (!sep)
			break ;
		beg = sep + 1;
	}
	return (NOK);
}

static void			msh_exe_hdl(int signo)
{
	(void)signo;
	ft_putc(1, '\n');
	ft_putc(0, '\n');
}

inline t_st			msh_exe_run(t_msh *self, t_vstr *av)
{
	pid_t	pid;
	int		st;
	char	exe[4096];

	if (ISE(st = msh_exe_lookup(self, av->buf[0], S_IFREG | S_IXUSR, exe)))
		return (ft_ret(NOK, "%s: %e", "msh", self->st = ST_TOENO(st)));
	if (ST_NOK(st))
		return (ft_ret(self->st = NOK, "%s: %s", "msh", "Command not found"));
	if (access(av->buf[0], X_OK) != 0)
		return (ft_ret(NOK, "%s: %e", "msh", self->st = errno));
	if (access(av->buf[0], R_OK) != 0)
		return (ft_ret(NOK, "%s: %e", "msh", self->st = errno));
	if ((pid = fork()) == 0)
		execve(av->buf[0], av->buf, self->env.buf);
	else if (pid < 0)
		return (ft_ret(NOK, "%s: %e", "msh", self->st = errno));
	signal(SIGINT, msh_exe_hdl);
	if (waitpid(pid, &st, 0) < 0)
		MSH_EXIT(EXIT_FAILURE, self);
	if (WIFEXITED(st))
		self->st = WEXITSTATUS(st);
	signal(SIGINT, msh_sigint_hdl);
	return (OK);
}
