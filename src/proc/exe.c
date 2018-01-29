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

#include "ush/eval.h"
#include "ush/proc.h"
#include "ush/bi.h"

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

static int		exelookup(char **env, char *exe, char *path, char *buf)
{
	int			st;
	int			rights;
	char		*beg;
	uint32_t	i;

	st = 0;
	if (ft_strchr(exe, '/'))
		return (exetest(ft_strcpy(buf, exe)));
	beg = sh_varget(path, env);
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

inline void		sh_procexe(t_proc *proc, char *path, char *exe, char **envv)
{
	t_procfn	*bi;

	sh_procctor(proc);
	proc->envv = envv;
	if ((bi = sh_bifn(exe)))
	{
		proc->u.fn = bi;
		proc->kind = PROC_FN;
	}
	else
	{
		proc->kind = PROC_EXE;
		proc->u.exe = ft_strdup(path);
	}
}

inline int		sh_procexelaunch(struct s_proc *prc)
{
	int		st;
	char 	buf[PATH_MAX + 1];

	if ((st = exelookup(prc->envv, prc->argv[0], prc->u.exe, buf)))
	{
		if (st == PROC_ISDIR)
			sh_err("%s: Is a directory\n", prc->argv[0]);
		else
			sh_err(st == PROC_NOTFOUND && !ft_strchr(prc->argv[0], '/') ?
			"%s: Command not found\n" : "%s: %e\n", prc->argv[0], errno);
		exit(st);
	}
	execve(buf, prc->argv, prc->envv);
	sh_err("%s: %e\n", prc->argv[0], errno);
	sh_procdtor(prc);
	exit(st);
}