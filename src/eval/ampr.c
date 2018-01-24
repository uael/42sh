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

#define EXPTD "Expected `<word>' after redirection `%s' got `%s'"

inline int			sh_evalampr(t_job *job, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_proc	*proc;
	t_redir	redir;

	if ((tok = sh_toknext(toks))->id != TOK_WORD)
		return (sh_evalerr(*ln, tok, EXPTD, sh_tokstr(tok)));
	proc = job && job->procs.len ? ft_vecback((t_vec *)&job->procs) : NULL;
	if (tok->id == TOK_WORD)
	{
		if ((redir.to = open(tok->val, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
			return (sh_evalerr(*ln, tok, "%s: %e", tok->val, errno));
		if (proc)
		{
			redir.from = STDOUT_FILENO;
			ft_veccpush((t_vec *)&proc->redirs, &redir);
			redir.from = STDERR_FILENO;
			ft_veccpush((t_vec *)&proc->redirs, &redir);
		}
		else
			g_shstatus = 0;
		sh_toknext(toks);
	}
	return (YEP);
}
