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

#include <sys/wait.h>

#include "ush/eval.h"

#define BUFS 4096

static char inline	*readproc(t_proc *p, t_sds *out)
{
	int		fds[2];
	int		io[3];
	int		status;
	ssize_t	ret;
	char	buf[BUFS + 1];

	ft_memcpy(io, STD_FILENOS, 3 * sizeof(int));
	if (pipe(fds) < 0)
		sh_exit(THROW(WUT), NULL);
	io[STDOUT_FILENO] = fds[1];
	p->close = fds[0];
	p->child = 1;
	if (sh_procfork(p, NULL, io, 1))
		return (NULL);
	waitpid(-p->pid, &status, WUNTRACED);
	close(fds[1]);
	while ((ret = read(fds[0], buf, BUFS)) > 0)
	{
		buf[ret] = 0;
		ft_sdsmpush(out, buf, (size_t)ret);
	}
	close(fds[0]);
	while (out->len && out->buf[--out->len] == '\n')
		out->buf[out->len] = '\0';
	return (out->buf);
}

inline t_tok		*sh_evalbackquote(t_tok *orig, t_deq *toks)
{
	t_proc	proc;
	t_tok	*tok;
	size_t	i;

	sh_procsh(&proc);
	tok = orig;
	++tok;
	while (tok->id != '`')
	{
		*(t_tok *)ft_deqpush(&proc.u.sh.toks) = *tok;
		i = (tok - (t_tok *)toks->buf) - toks->cur;
		ft_deqrem(toks, i, NULL);
		tok = ft_deqat(toks, i);
	}
	ft_deqrem(toks, (tok - (t_tok *)toks->buf) - toks->cur, NULL);
	(*(t_tok *)ft_deqpush(&proc.u.sh.toks)).id = TOK_END;
	orig->len = 0;
	orig->id = TOK_WORD;
	if (proc.u.sh.toks.len)
		readproc(&proc, (t_sds *)orig);
	sh_procdtor(&proc);
	return (orig);
}
