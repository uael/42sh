/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
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

inline t_st		sh_exe_av(t_sh *self, t_vstr *av, char *exe)
{
	t_tok *end;

	if (av)
		ft_vstr_ctor(av);
	if (av && !ft_vstr_pushc(av, exe))
		return (ENO);
	while ((end = sh_peek(self)) && end->id)
	{
		if (end->id == SH_TOK_WORD && av &&
			!ft_vstr_pushc(av, ft_tok_ident(end)->buf))
			return (ENO);
		else if (end->id != SH_TOK_WORD && !ft_strchr(" \t", end->id))
			break ;
		sh_next(self, NULL);
	}
	if (av && !ft_vstr_grow(av, 1))
		return (ENO);
	if (av)
		FT_INIT(ft_vstr_end(av), char *);
	return (OK);
}

static t_st		exe_test(char *exe)
{
	struct stat s;

	if (!*exe || lstat(exe, &s) < 0 || !(s.st_mode & (S_IFREG | S_IXUSR)))
		return (NOK);
	return (OK);
}

static t_st		exe_lookup(t_vstr *env, char *f, char *p, char *exe)
{
	char	**path;
	char	*beg;
	char	*sep;
	size_t	len;
	t_st	st;

	if (ST_OK(st = exe_test(ft_strcpy(exe, f))) || ISE(st))
		return (st);
	if (!(path = sh_getenv(env, p)))
		return (exe_test(ft_strcat(ft_strcpy(exe, "/bin/"), f)));
	beg = *path + 5;
	while ((sep = ft_strchr(beg, ':')) >= 0)
	{
		len = sep ? sep - beg : ft_strlen(beg);
		ft_strncpy(exe, beg, len)[len] = '\0';
		ft_pathcat(exe, f);
		if (ST_OK(st = exe_test(exe)) || ISE(st))
			return (st);
		if (!sep)
			break ;
		beg = sep + 1;
	}
	return (NOK);
}

static void		exe_hdl(int signo)
{
	(void)signo;
	ft_putc(1, '\n');
	ft_putc(0, '\n');
}

inline t_st		sh_exe_run(t_sh *self, char *p, t_vstr *av, t_vstr *env)
{
	pid_t	pid;
	int		st;
	char	exe[PATH_MAX + 1];

	if (ISE(st = exe_lookup(env, av->buf[0], p, exe)))
		return (ft_ret(NOK, "%s: %e\n", av->buf[0], self->st = ST_TOENO(st)));
	if (ST_NOK(st))
		return (ft_ret(self->st = NOK, "%s: Command not found\n", av->buf[0]));
	if (access(exe, R_OK) != 0)
		return (ft_ret(NOK, "%s: %e\n", av->buf[0], self->st = errno));
	if (access(exe, X_OK) != 0)
		return (ft_ret(NOK, "%s: %e\n", av->buf[0], self->st = errno));
	if ((pid = fork()) == 0)
		execve(exe, av->buf, env->buf);
	else if (pid < 0)
		return (ft_ret(NOK, "%s: %e\n", av->buf[0], self->st = errno));
	signal(SIGINT, exe_hdl);
	if (waitpid(pid, &st, 0) < 0)
		SH_EXIT(EXIT_FAILURE, self, NULL);
	if (WIFEXITED(st))
		self->st = WEXITSTATUS(st);
	signal(SIGINT, sh_sigint_hdl);
	return (OK);
}
