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

static int		g_iodfl[3] = {STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO};

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

static int		exelookup(char **env, char *exe, char *path, char *buf)
{
	char		*beg;
	char		*sep;
	size_t		len;
	uint32_t	i;
	int			st;
	int			rights;

	if (!(st = exetest(ft_strcpy(buf, exe))))
		return (st);
	rights = st == PROC_NORIGHTS;
	if (!(beg = ft_getenv(env, path)))
		return (PROC_NOTFOUND);
	if (ft_mapget(g_binaries, exe, &i))
	{
		if (!(st = exetest(ft_strcpy(buf, ((char **)g_binaries->vals)[i]))) ||
			st == PROC_NORIGHTS)
			return (st);
	}
	while (1)
	{
		sep = ft_strchr(beg, ':');
		len = sep ? (size_t)(sep - beg) : ft_strlen(beg);
		ft_strncpy(buf, beg, len)[len] = '\0';
		if (!(st = exetest(ft_pathcat(buf, exe))) || st == PROC_NORIGHTS)
		{
			ft_mapput(g_binaries, exe, &i);
			((char **)g_binaries->vals)[i] = ft_strdup(buf);
			return (st);
		}
		if (!sep)
			break ;
		beg = sep + 1;
	}
	return (rights ? PROC_NORIGHTS : PROC_NOTFOUND);
}

inline void		sh_procfn(t_proc *proc, t_procfn *fn, char **envv)
{
	ft_memset(proc, 0, sizeof(t_proc));
	proc->envv = envv;
	proc->u.fn = fn;
	proc->kind = PROC_FN;
	ft_vecctor((t_vec *)&proc->redirs, sizeof(t_redir));
	ft_memset(proc->scope, -1, 3 * sizeof(int));
	ft_memcpy(proc->src, g_iodfl, 3 * sizeof(int));
}

inline void		sh_proccmderr(t_proc *proc, char *ln, t_tok *tok, int st)
{
	proc->kind = PROC_CNF;
	if ((proc->u.cnf.ln = ln))
		proc->u.cnf.it = ln + tok->pos;
	if (tok)
		proc->u.cnf.exe = tok->val;
	proc->u.cnf.st = st;
}

inline int		sh_procsh(t_proc *proc, t_deq *toks, char *ln)
{
	int		stack;
	t_tok	*tok;

	ft_memset(proc, stack = 0, sizeof(t_proc));
	ft_deqctor(&proc->u.sh.toks, sizeof(t_tok));
	proc->u.sh.ln = ln;
	if (toks)
	{
		while ((tok = sh_toknext(toks))->id != ')' && !stack)
		{
			if (tok->id == '(')
				++stack;
			else if (tok->id == ')')
				--stack;
			*(t_tok *)ft_deqpush(&proc->u.sh.toks) = *tok;
		}
		if (!proc->u.sh.toks.len)
			return (NOP);
		(*(t_tok *)ft_deqpush(&proc->u.sh.toks)).id = TOK_END;
	}
	proc->kind = PROC_SH;
	ft_vecctor((t_vec *)&proc->redirs, sizeof(t_redir));
	ft_memset(proc->scope, -1, 3 * sizeof(int));
	ft_memcpy(proc->src, g_iodfl, 3 * sizeof(int));
	return (YEP);
}

inline int		sh_procctor(t_proc *proc, char *path, char *exe, char **envv)
{
	int		st;
	char	buf[PATH_MAX + 1];

	ft_memset(proc, 0, sizeof(t_proc));
	ft_vecctor((t_vec *)&proc->redirs, sizeof(t_redir));
	ft_memset(proc->scope, -1, 3 * sizeof(int));
	ft_memcpy(proc->src, g_iodfl, 3 * sizeof(int));
	proc->envv = envv;
	if (!ft_strcmp(exe, "cd"))
	{
		proc->u.fn = sh_bicd;
		proc->kind = PROC_FN;
	}
	else if (!ft_strcmp(exe, "echo"))
	{
		proc->u.fn = sh_biecho;
		proc->kind = PROC_FN;
	}
	else if (!ft_strcmp(exe, "env"))
	{
		proc->u.fn = sh_bienv;
		proc->kind = PROC_FN;
	}
	else if (!ft_strcmp(exe, "exit"))
	{
		proc->u.fn = sh_biexit;
		proc->kind = PROC_FN;
	}
	else if (!ft_strcmp(exe, "setenv"))
	{
		proc->u.fn = sh_bisetenv;
		proc->kind = PROC_FN;
	}
	else if (!ft_strcmp(exe, "unsetenv"))
	{
		proc->u.fn = sh_biunsetenv;
		proc->kind = PROC_FN;
	}
	else if ((st = exelookup(envv, exe, path, buf)))
		return (st);
	else
		proc->u.exe = ft_strdup(buf);
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
	ft_vecdtor((t_vec *)&proc->redirs, NULL);
	if (proc->kind == PROC_SH)
		ft_deqdtor(&proc->u.sh.toks, NULL);
}
