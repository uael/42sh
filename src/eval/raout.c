/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/raout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

#define UEH "Expected `<filename>' got `%s'"

inline int		sh_evalraout(t_job *job, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_proc	*proc;
	t_redir	redir;
	t_tok	*op;
	char	buf[PATH_MAX];

	op = sh_tokpeek(toks);
	if (!(tok = sh_toknext(toks)) || !TOK_ISWORD(tok->id))
		return (sh_evalerr(*ln, tok, UEH, sh_tokstr(tok)));
	if (!(tok = sh_redirword(job, toks, *ln)))
		return (YEP);
	proc = ft_vecback((t_vec *)&job->procs);
	if ((redir.to = open(tok->val, O_WRONLY | O_APPEND, 0644)) < 0)
	{
		sh_procerr(proc, ft_strcat(ft_strcat(ft_strcpy(buf, tok->val), ": "),
			ft_strerr(errno)), *ln, tok->pos);
		return (YEP);
	}
	redir.from = ft_isdigit(*op->val) ? *op->val - '0' : STDOUT_FILENO;
	*(t_redir *)ft_vecpush((t_vec *)&proc->redirs) = redir;
	return (YEP);
}
