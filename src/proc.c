/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

#include "ush/proc.h"
#include "ush/eval.h"
#include "ush/bi.h"

static int		exetest(char *exe)
{
	struct stat s;

	if (!*exe || lstat(exe, &s) < 0)
		return (PROC_NOTFOUND);
	if (!(s.st_mode & (S_IFREG | S_IXUSR)))
		return (PROC_NOTFOUND);
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
		if (!(st = exetest(ft_pathcat(buf, exe))) || st == PROC_NORIGHTS)
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

	if (!(st = exetest(ft_strcpy(buf, exe))))
		return (st);
	rights = st == PROC_NORIGHTS;
	if (!(beg = sh_varget(path)) &&
		!(beg = ft_getenv(env, path)))
		return (PROC_NOTFOUND);
	if (ft_mapget(g_binaries, exe, &i))
	{
		if (!(st = exetest(ft_strcpy(buf, ((char **)g_binaries->vals)[i]))) ||
			st == PROC_NORIGHTS)
			return (st);
	}
	return (exelookuppath(beg, exe, rights, buf));
}

inline int		sh_procctor(t_proc *proc, char *path, char *exe, char **envv)
{
	int			st;
	t_procfn	*bi;
	char		buf[PATH_MAX + 1];

	ft_memset(proc, 0, sizeof(t_proc));
	ft_vecctor((t_vec *)&proc->redirs, sizeof(t_redir));
	ft_memset(proc->scope, -1, 3 * sizeof(int));
	ft_memcpy(proc->src, STD_FILENOS, 3 * sizeof(int));
	proc->envv = envv;
	if ((bi = sh_bifn(exe)))
	{
		proc->u.fn = bi;
		proc->kind = PROC_FN;
	}
	else if ((st = exelookup(envv, exe, path, buf)))
		return (st);
	else
	{
		proc->kind = PROC_EXE;
		proc->u.exe = ft_strdup(buf);
	}
	return (YEP);
}

inline void		sh_procdtor(t_proc *proc)
{
	char **av;

	if ((av = proc->argv))
	{
		while (*av)
			free(*av++);
		free(proc->argv);
		proc->argv = NULL;
	}
	if (proc->ownenv && (av = proc->envv))
	{
		while (*av)
			free(*av++);
		free(proc->envv);
		proc->envv = NULL;
	}
	ft_vecdtor((t_vec *)&proc->redirs, NULL);
	if (proc->kind == PROC_SH)
		ft_deqdtor(&proc->u.sh.toks, NULL);
	else if (proc->kind == PROC_EXE)
		free(proc->u.exe);
}
