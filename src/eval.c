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

static void	evalsemicolon(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	sh_toknext(ctx->toks);
	if (!ctx->root->procs.len)
		return ;
	sh_evalexport(&ctx->vars);
	g_sh->status = ps_joblaunch(ctx->root, 1);
	ps_jobctor(ctx->root);
	ctx->job = ctx->root;
	ctx->proc = NULL;
}

static void	evalampersand(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	sh_evalexport(&ctx->vars);
	sh_toknext(ctx->toks);
	g_sh->status = ps_joblaunch(ps_poolpush(ctx->root), 0);
	ps_jobctor(ctx->root);
	ctx->job = ctx->root;
	ctx->proc = NULL;
}

t_evalcb	*g_eval[] = {
	[TOK_IF] = sh_evalif,
	[TOK_WHILE] = sh_evalwhile,
	[TOK_UNTIL] = sh_evaluntil,
	[TOK_FOR] = sh_evalfor,
	[TOK_FUNCTION] = sh_evalfuncdef,
	[TOK_AMPR] = sh_evalampr,
	[TOK_AMPRA] = sh_evalampra,
	[TOK_CMP] = sh_evalcmp,
	[TOK_HEREDOC] = sh_evalheredoc,
	[TOK_HERENOW] = sh_evalherenow,
	[TOK_LAMP] = sh_evallamp,
	[TOK_RAMP] = sh_evalramp,
	[TOK_RAOUT] = sh_evalraout,
	[TOK_WORD] = sh_evalword,
	[TOK_DLBRA] = sh_evaltest,
	[TOK_ASSIGN] = sh_evalassign,
	[TOK_LAND] = sh_evaland,
	[TOK_LOR] = sh_evalor,
	[TOK_PIPEAND] = sh_evalpipeand,
	['!'] = sh_evalbang,
	['('] = sh_evalsubshell,
	['{'] = sh_evalbracegrp,
	['<'] = sh_evalrin,
	['>'] = sh_evalrout,
	['|'] = sh_evalpipe,
	[';'] = evalsemicolon,
	['\n'] = evalsemicolon,
	['\0'] = evalsemicolon,
	['&'] = evalampersand,
};

void		sh_eval(t_deq *toks, char const *ln)
{
	t_ctx	ctx;
	t_tok	*tok;
	t_job	job;

	ft_bzero(&ctx, sizeof(t_ctx));
	ps_jobctor(ctx.root = &job);
	ft_mapctor(&ctx.vars, g_strhash, sizeof(char *), sizeof(char *));
	ctx.job = ctx.root;
	ctx.ln = ln;
	ctx.stop = toks->len;
	ctx.toks = toks;
	while (ctx.toks->cur < ctx.stop && ctx.toks->cur < ctx.toks->len)
	{
		tok = ft_deqbeg(ctx.toks);
		if (!g_eval[tok->id])
			sh_toknext(ctx.toks);
		else
			g_eval[tok->id](&ctx, tok);
		if (tok->id == TOK_END)
			break ;
	}
	ps_jobdtor(ctx.root);
	ft_mapdtor(&ctx.vars, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
}

void		sh_pushuntil(t_deq *d, t_deq *s, char const *stop, char const *oc)
{
	t_tok	*tok;
	int		depth;

	depth = 0;
	while (!ft_strchr(stop, (tok = sh_toknext(s))->id) || depth)
	{
		if (tok->id == oc[0])
			++depth;
		else if (tok->id == oc[1])
			--depth;
		if (d)
			*(t_tok *)ft_deqpush(d) = *tok;
	}
	if (d)
		(*(t_tok *)ft_deqpush(d)).id = TOK_END;
}
