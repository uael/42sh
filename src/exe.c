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

#include "msh.h"

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

inline t_ret		msh_exe_lookup(t_msh *self, char *f, int mode, char exe[])
{
	char		**path;
	char		*beg;
	char		*sep;
	struct stat	s;

	if (!*f)
		return (RET_NOK);
	if ((*f == '/' || *f == '.') && ft_strcpy(exe, f))
		return (RET_OK);
	if (!(path = msh_getenv(self, "PATH")))
		return (RET_NOK);
	beg = *path + 5;
	while ((sep = ft_strchr(beg, ':')))
	{
		ft_strncpy(exe, beg, sep - beg)[sep - beg] = '\0';
		ft_pathcat(exe, f);
		if (lstat(exe, &s) == 0 && (s.st_mode & mode))
			return (RET_OK);
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

	if ((pid = fork()) == 0)
		execve(av->buf[0], av->buf, self->env.buf);
	else if (pid < 0)
		return (RET_ERR);
	signal(SIGINT, msh_exe_hdl);
	wait(&pid);
	signal(SIGINT, msh_sigint_hdl);
	return (RET_OK);
}
