/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/andor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

#define UNXPTD "syntax error: Unexpected bang `%s' for empty pipeline"
#define UEH "syntax error: Expected <pipeline> got `%s'"
#define UEP "syntax error: Missing right operand after `%s'"
#define EB 1 << 1
#define EI 1 << 2

static inline int	perr(int st, t_tok *tok, int flags, char *ln)
{
	if (st == NOP && (flags & EB))
		return (sh_evalerr(ln, tok, UNXPTD, sh_tokstr(tok)));
	if (st == NOP && (flags & EI))
	{
		if (tok->id == TOK_LAND || tok->id == TOK_LOR)
			return (sh_evalerr(ln, tok, UEP, sh_tokstr(tok)));
		return (sh_evalerr(ln, tok, UEH, sh_tokstr(tok)));
	}
	return (st);
}

static int			separator(t_deq *toks, t_job *right, t_tok *tok,
	char const *ln)
{
	while ((tok = sh_toknext(toks)))
		if (tok->id != TOK_EOL)
			break ;
	ps_jobctor(right);
	if (!(tok = sh_tokpeek(toks)))
		return (NOP);
	if (tok->len == 1 && *(ln + tok->pos) == '!')
	{
		right->bang = 1;
		sh_toknext(toks);
	}
	return (YEP);
}

inline int			sh_evalandor(t_job *j, int fd, t_deq *ts, char **ln)
{
	t_tok	*t;
	t_job	r;
	int		st;

	if (!(t = sh_tokpeek(ts)))
		return (NOP);
	t->len == 1 && *(*ln + t->pos) == '!' && (j->bang = 1)
		? sh_toknext(ts) : 0;
	if ((st = sh_evalpipeline(j, fd, ts, ln)))
		return (perr(st, t, j->bang ? EB : 0, *ln));
	while (1)
		if (!(t = sh_tokpeek(ts)))
			return (NOP);
		else if (t->id == TOK_LAND || t->id == TOK_LOR)
		{
			if (separator(ts, &r, t, *ln))
				return (sh_evalerr(*ln, t, UEP, sh_tokstr(t)));
			if ((st = sh_evalpipeline(&r, fd, ts, ln)))
				return (perr(st, sh_tokpeek(ts), (r.bang ? EB : 0) | EI, *ln));
			j = ps_jobnext(j, &r, t->id == TOK_LAND ? ANDOR_AND : ANDOR_OR);
		}
		else
			return (YEP);
}
