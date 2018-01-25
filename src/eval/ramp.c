/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/ramp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

#define EXPTD "Expected `<word>' after redirection `%s' got `%s'"

inline int			sh_evalramp(t_job *job, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_proc	*proc;
	t_redir	r;
	t_tok	*op;
	char	buf[PATH_MAX];

	op = sh_tokpeek(toks);
	if ((tok = sh_toknext(toks))->id != TOK_WORD)
		return (sh_evalerr(*ln, tok, EXPTD, sh_tokstr(op), sh_tokstr(tok)));
	sh_toknext(toks);
	proc = ft_vecback((t_vec *)&job->procs);
	if (ft_strcmp(tok->val, "-") == 0)
		r.to = -1;
	else if (ft_isdigit(*tok->val) && ft_strlen(tok->val) == 1)
		r.to = *tok->val - '0';
	else if ((r.to = open(tok->val, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
	{
		sh_procerr(proc, ft_strdup(ft_strcat(ft_strcat(
			ft_strcpy(buf, tok->val), ": "), ft_strerr(errno))), tok, *ln);
		return (YEP);
	}
	r.from = ft_isdigit(*op->val) ? *op->val - '0' : STDOUT_FILENO;
	*(t_redir *)ft_vecpush((t_vec *)&proc->redirs) = r;
	return (YEP);
}
