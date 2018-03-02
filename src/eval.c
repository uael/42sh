/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 13:39:06 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static void		evalcmd(t_ectx *ctx);

static void		evalif(t_ectx *ctx)
{

}

static void		evalwhile(t_ectx *ctx)
{

}

static void		evalfuncdef(t_ectx *ctx)
{

}

static void		evalsubshell(t_ectx *ctx)
{

}

static void		evalbracegrp(t_ectx *ctx)
{

}

static void		evalampr(t_ectx *ctx)
{

}

static void		evalcmp(t_ectx *ctx)
{

}

static void		evalheredoc(t_ectx *ctx)
{

}

static void		evallamp(t_ectx *ctx)
{

}

static void		evalramp(t_ectx *ctx)
{

}

static void		evalraout(t_ectx *ctx)
{

}

static void		evalrin(t_ectx *ctx)
{

}

static void		evalrout(t_ectx *ctx)
{

}

static void		evalsimple(t_ectx *ctx)
{

}

static void		evalassign(t_ectx *ctx)
{

}

typedef void	(t_evalcb)(t_ectx *ctx);

static t_evalcb	*g_eval[] = {
	[TOK_IF] = evalif,
	[TOK_WHILE] = evalwhile,
	[TOK_FUNCTION] = evalfuncdef,
	['('] = evalsubshell,
	['{'] = evalbracegrp,
	[TOK_AMPR] = evalampr,
	[TOK_CMP] = evalcmp,
	[TOK_HEREDOC] = evalheredoc,
	[TOK_LAMP] = evallamp,
	[TOK_RAMP] = evalramp,
	[TOK_RAOUT] = evalraout,
	['<'] = evalrin,
	['>'] = evalrout,
	[TOK_WORD] = evalsimple,
	[TOK_ASSIGN] = evalassign
};

static void		evalcmd(t_ectx *ctx)
{
	t_tok	*tok;

	if (ctx->toks->cur >= ctx->stop)
		return ;
	tok = ft_deqbeg(ctx->toks);
	if (!sh_tokidis(tok->id, TOKS_LEFT | TOKS_WORD | TOKS_REDIR))
		return ;
	g_eval[tok->id](ctx);
	return (evalcmd(ctx));
}

inline void		evalpipeline(t_job *job, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_proc	proc;

	ps_procctor(&proc);
	tok = sh_tokpeek(toks);
	tok->id == TOK_BANG && (job->bang = 1) ? sh_toknext(toks) : 0;
	evalcmd(&proc, toks, ln);
	*(t_proc *)ft_vecpush((t_vec *)&job->procs) = proc;
	while ((tok = sh_tokpeek(toks)) && tok->id == '|')
	{
		g_sh->child = 0;
		ps_procctor(&proc);
		sh_toknext(toks);
		evalcmd(&proc, toks, ln);
		*(t_proc *)ft_vecpush((t_vec *)&job->procs) = proc;
	}
}

inline t_bool	evalandor(t_ectx *ctx)
{
	t_tok *tok;
	t_job rigth;
	t_job *job;

	if (ctx->toks->cur >= ctx->stop || !(tok = sh_tokpeek(ctx->toks)))
		return (0);
	if (tok->id == TOK_END)
		return (1);
	evalpipeline(ctx);
	job = ctx->job;
	while (1)
		if (ctx->toks->cur >= ctx->stop || !(tok = sh_tokpeek(ctx->toks)))
			return (0);
		else if (tok->id == TOK_LAND || tok->id == TOK_LOR)
		{
			sh_toknext(ctx->toks);
			evalpipeline(ctx);
			job = ps_jobnext(job, &ctx->job,
				tok->id == TOK_LAND ? ANDOR_AND : ANDOR_OR);
		}
		else
			return (1);
}

inline void		eval(t_deq *toks, char const *ln)
{
	t_ectx	ctx;
	t_tok	*tok;
	t_job	job;

	ft_bzero(&ctx, sizeof(t_ectx));
	ps_jobctor(ctx.job = &job);
	ctx.ln = ln;
	ctx.stop = toks->len;
	ctx.toks = toks;
	while (evalandor(&ctx))
	{
		tok = sh_toknext(toks);
		if (tok->id == '&')
			g_sh->status = ps_joblaunch(ps_poolpush(ctx.job), 0);
		else
			ps_joblaunch(ctx.job, 1);
		ps_jobctor(ctx.job);
	}
	ps_jobdtor(ctx.job);
}
