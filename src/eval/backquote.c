/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/backquote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wait.h>

#include "ush/eval.h"

#define BUF_SIZE	4096

static char		*readfd0(int *fds, t_sds *out)
{
	ssize_t	ret;
	char	buf[BUF_SIZE + 1];

	close(fds[1]);
	while ((ret = read(fds[0], buf, BUF_SIZE)) > 0)
	{
		buf[ret] = 0;
		ft_sdsmpush(out, buf, (size_t)ret);
	}
	close(fds[0]);
	while (out->len && out->buf[--out->len] == '\n')
		out->buf[out->len] = '\0';
	return (out->buf);
}

char			*readproc(t_proc *p, t_sds *out)
{
	int			ret;
	int			pid;
	int			fds[2];
	int			io[3];

	ft_memcpy(io, STD_FILENOS, 3 * sizeof(int));
	if (pipe(fds) < 0)
		sh_exit(THROW(WUT), NULL);
	io[STDOUT_FILENO] = fds[1];
	p->child = 1;
	p->close = fds[0];
	p->state = PROC_RUNNING;
	if (!(pid = fork()))
		sh_proclaunch(p, 0, io, 1);
	else if (pid < 0)
		sh_exit(THROW(WUT), NULL);
	p->pid = pid;
	g_sh->ppid = pid;
	if (g_sh->tty)
		setpgid(pid, 0);
	waitpid(pid, &ret, WUNTRACED);
	return (readfd0(fds, out));
}

inline t_tok	*sh_evalbackquote(t_deq *toks)
{
	t_proc	proc;
	t_tok	*tok;

	sh_procsh(&proc);
	while ((tok = sh_toknext(toks))->id != '`')
		*(t_tok *)ft_deqpush(&proc.u.sh.toks) = *tok;
	*tok->val = '\0';
	tok->len = 0;
	tok->id = TOK_WORD;
	tok->spec |= TSPEC_DQUOTE;
	if (proc.u.sh.toks.len)
		readproc(&proc, (t_sds *)tok);
	sh_procdtor(&proc);
	return (tok);
}
