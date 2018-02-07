/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc/exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

#include "../ps.h"

static int		exetest(char *exe)
{
	struct stat s;

	if (!*exe || lstat(exe, &s) < 0)
		return (PROC_NOTFOUND);
	if (!(s.st_mode & (S_IFREG | S_IXUSR)))
		return (PROC_NOTFOUND);
	if (S_ISDIR(s.st_mode))
		return (PROC_ISDIR);
	if (access(exe, X_OK) != 0)
		return (PROC_NORIGHTS);
	return (YEP);
}

static int		exelookuppath(char *pvar, char *exe, int rights, char *buf)
{
	char		*sep;
	size_t		len;
	uint32_t	i;
	int			st;

	while (1)
	{
		sep = ft_strchr(pvar, ':');
		len = sep ? (size_t)(sep - pvar) : ft_strlen(pvar);
		ft_strncpy(buf, pvar, len)[len] = '\0';
		if (!(st = exetest(ft_pathcat(buf, exe))) || st == PROC_NORIGHTS ||
			st == PROC_ISDIR)
		{
			ft_mapput(g_binaries, ft_strdup(exe), &i);
			((char **)g_binaries->vals)[i] = ft_strdup(buf);
			return (st);
		}
		if (!sep)
			break ;
		pvar = sep + 1;
	}
	return (rights ? PROC_NORIGHTS : PROC_NOTFOUND);
}

static int		exelookup(char **env, char *exe, char const *path, char *buf)
{
	int			st;
	int			rights;
	char		*beg;
	uint32_t	i;

	st = 0;
	if (ft_strchr(exe, '/'))
		return (exetest(ft_strcpy(buf, exe)));
	beg = ft_getenv(env, path);
	if (beg && !ft_strlen(beg) && !(st = exetest(ft_strcpy(buf, exe))))
		return (st);
	rights = st == PROC_NORIGHTS;
	if (!beg)
		return (PROC_NOTFOUND);
	if (ft_mapget(g_binaries, exe, &i))
	{
		if (!(st = exetest(ft_strcpy(buf, ((char **)g_binaries->vals)[i]))) ||
			st == PROC_NORIGHTS)
			return (st);
	}
	return (exelookuppath(beg, exe, rights, buf));
}

inline void		ps_procexe(t_proc *p, char const *path, char *exe, char **envv)
{
	uint32_t	it;

	ps_procctor(p);
	p->envv = envv;
	if (ft_mapget(g_builtins, exe, &it))
	{
		p->u.bi = ((t_procbi **)g_builtins->vals)[it];
		p->kind = PROC_BI;
	}
	else
	{
		p->kind = PROC_EXE;
		p->u.exe.pvar = path;
	}
}

inline int		ps_procexelaunch(struct s_proc *prc)
{
	int		st;
	char	buf[PATH_MAX + 1];

	if ((st = exelookup(prc->envv, prc->argv[0], prc->u.exe.pvar, buf)))
	{
		if (st == PROC_ISDIR)
			g_errcb("%s: Is a directory\n", prc->argv[0]);
		else
			g_errcb(st == PROC_NOTFOUND && !ft_strchr(prc->argv[0], '/') ?
			"%s: Command not found\n" : "%s: %e\n", prc->argv[0], errno);
		g_fatalcb(st, NULL);
	}
	execve(buf, prc->argv, prc->envv);
	g_errcb("%s: %e\n", prc->argv[0], errno);
	ps_procdtor(prc);
	return (g_fatalcb(st, NULL));
}
