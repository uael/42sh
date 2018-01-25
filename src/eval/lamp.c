/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/lamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

#define EXPTD "Expected `<word>' after redirection `%s' got `%s'"

inline int			sh_evallamp(t_job *job, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_proc	*proc;
	t_redir	redir;
	t_tok	*op;

	op = sh_tokpeek(toks);
	if ((tok = sh_toknext(toks))->id != TOK_WORD)
		return (sh_evalerr(*ln, tok, EXPTD, sh_tokstr(op), sh_tokstr(tok)));
	proc = ft_vecback((t_vec *)&job->procs);
	redir.from = ft_isdigit(*op->val) ? *op->val - '0' : STDIN_FILENO;
	redir.filename = NULL;
	if (ft_strcmp(tok->val, "-") == 0)
		redir.to = -1;
	else if (ft_isdigit(*tok->val) && ft_strlen(tok->val) == 1)
		redir.to = *tok->val - '0';
	else if ((redir.filename = tok->val))
		redir.to = -1;
	redir.flags = O_RDONLY;
	redir.tok = tok;
	redir.ln = *ln;
	*(t_redir *)ft_vecpush((t_vec *)&proc->redirs) = redir;
	sh_toknext(toks);
	return (YEP);
}
