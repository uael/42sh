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

#define EXIST(F, S) (lstat((F), &(S)) == 0 && ((S).st_mode & mode))

inline t_ret		msh_exe_av(t_msh *self, t_vstr *av, char *exe)
{
	t_tok *end;

	if (av)
		ft_vstr_ctor(av);
	if (av && !ft_vstr_pushc(av, exe))
		return (RET_ERR);
	while ((end = msh_peek(self)) && end->id)
	{
		if (end->id == MSH_TOK_WORD && av &&
			!ft_vstr_pushc(av, ft_tok_ident(end)->buf))
			return (RET_ERR);
		else if (end->id != MSH_TOK_WORD && !ft_strchr(" \t", end->id))
			break ;
		msh_next(self, NULL);
	}
	if (av && !ft_vstr_grow(av, 1))
		return (RET_ERR);
	if (av)
		FT_INIT(ft_vstr_end(av), char *);
	return (RET_OK);
}

static t_ret		msh_exe_test(char *exe, int mode)
{
	struct stat	s;
	char		path[PATH_MAX + 1];
	int			i;
	ssize_t		l;

	i = -1;
	while (++i <= 40)
	{
		if (!*exe || lstat(exe, &s) < 0 || !(s.st_mode & mode))
			return (RET_NOK);
		if (!S_ISLNK(s.st_mode) || !(l = readlink(exe, path, PATH_MAX)))
			return (RET_OK);
		path[l] = '\0';
		ft_strcpy(exe, path);
	}
	ft_putl(2, "msh: Too many symbolic links");
	return (RET_ERR);
}

inline t_ret		msh_exe_lookup(t_msh *self, char *f, int mode, char exe[])
{
	char	**path;
	char	*beg;
	char	*sep;
	size_t	len;
	t_ret	r;

	if ((r = msh_exe_test(ft_strcpy(exe, f), mode)) <= 0)
		return (r);
	if (!(path = msh_getenv(self, "PATH")))
		return (msh_exe_test(ft_strcat(ft_strcpy(exe, "/bin/"), f), mode));
	beg = *path + 5;
	while ((sep = ft_strchr(beg, ':')) >= 0)
	{
		len = sep ? sep - beg : ft_strlen(beg);
		ft_strncpy(exe, beg, len)[len] = '\0';
		ft_pathcat(exe, f);
		if ((r = msh_exe_test(exe, mode)) <= 0)
			return (r);
		if (!sep)
			break ;
		beg = sep + 1;
	}
	return (RET_NOK);
}

static void			msh_exe_hdl(int signo)
{
	(void)signo;
	ft_putc(1, '\n');
	ft_putc(0, '\n');
}

inline t_ret		msh_exe_run(t_msh *self, t_vstr *av)
{
	pid_t	pid;
	int		st;

	if (access(av->buf[0], X_OK) != 0)
		return ((t_ret)(self->st = CMD_NOK("msh: Permission denied")));
	if ((pid = fork()) == 0)
		execve(av->buf[0], av->buf, self->env.buf);
	else if (pid < 0)
		return (RET_ERR);
	signal(SIGINT, msh_exe_hdl);
	if (waitpid(pid, &st, 0) < 0)
		MSH_EXIT(EXIT_FAILURE, self);
	if (WIFEXITED(st))
		self->st = WEXITSTATUS(st);
	signal(SIGINT, msh_sigint_hdl);
	return (RET_OK);
}
