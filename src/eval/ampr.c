/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/ampr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

#define UEH "Expected `<word>' after redirection `%s' got `%s'"
#define AMB ": Ambiguous redirect\n"

inline char		*sh_redirword(t_job *job, char *dst, t_deq *toks, char *ln)
{
	t_tok	*tok;
	t_proc	*proc;
	char	buf[PATH_MAX + 1];

	proc = ft_vecback((t_vec *)&job->procs);
	tok = sh_tokpeek(toks);
	if (!sh_tokexpand(dst, tok, ln, PATH_MAX))
	{
		sh_procerr(proc, ft_strcat(ft_strncpy(buf, ln + tok->pos,
			ft_u64max(tok->len, PATH_MAX)), AMB), ln, tok->pos);
		return (NULL);
	}
	sh_toknext(toks);
	return (dst);
}

inline int			sh_evalampr(t_job *job, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_proc	*proc;
	int		fd;
	char	buf[PATH_MAX];

	if (!(tok = sh_toknext(toks)) || !TOK_ISWORD(tok->id))
		return (sh_evalerr(*ln, tok, UEH, sh_tokstr(tok)));
	if (!sh_redirword(job, buf, toks, *ln))
		return (YEP);
	proc = ft_vecback((t_vec *)&job->procs);
	if ((fd = open(buf, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
	{
		sh_procerr(proc, ft_strcat(ft_strcat(buf, ": "),
			ft_strerr(errno)), *ln, tok->pos);
		return (YEP);
	}
	*(t_redir *)ft_vecpush((t_vec *)&proc->redirs) =
		(t_redir){fd, STDOUT_FILENO};
	*(t_redir *)ft_vecpush((t_vec *)&proc->redirs) =
		(t_redir){fd, STDERR_FILENO};
	return (YEP);
}
