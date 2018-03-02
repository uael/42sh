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

static void		evalif(t_ctx *ctx, t_tok *tok)
{

}

static void		evalwhile(t_ctx *ctx, t_tok *tok)
{

}

static void		evalfuncdef(t_ctx *ctx, t_tok *tok)
{

}

static void		evalsubshell(t_ctx *ctx, t_tok *tok)
{

}

static void		evalbracegrp(t_ctx *ctx, t_tok *tok)
{

}

static void		evalampr(t_ctx *ctx, t_tok *tok)
{

}

static void		evalcmp(t_ctx *ctx, t_tok *tok)
{

}

static void		evalheredoc(t_ctx *ctx, t_tok *tok)
{

}

static void		evallamp(t_ctx *ctx, t_tok *tok)
{

}

static void		evalramp(t_ctx *ctx, t_tok *tok)
{

}

static void		evalraout(t_ctx *ctx, t_tok *tok)
{

}

static void		evalrin(t_ctx *ctx, t_tok *tok)
{

}

static void		evalrout(t_ctx *ctx, t_tok *tok)
{

}

static void		evalword(t_ctx *ctx, t_tok *tok)
{

}

static void		evaltest(t_ctx *ctx, t_tok *tok)
{

}

static void		evalassign(t_ctx *ctx, t_tok *tok)
{

}

inline void		evalpipe(t_ctx *ctx, t_tok *tok)
{

}

inline void		evaland(t_ctx *ctx, t_tok *tok)
{

}

inline void		evalor(t_ctx *ctx, t_tok *tok)
{

}

inline void		evalsemicolon(t_ctx *ctx, t_tok *tok)
{

}

inline void		evalampersand(t_ctx *ctx, t_tok *tok)
{

}

typedef void	(t_evalcb)(t_ctx *ctx, t_tok *tok);

static t_evalcb	*g_eval[] = {
	[TOK_IF] = evalif,
	[TOK_WHILE] = evalwhile,
	[TOK_FUNCTION] = evalfuncdef,
	[TOK_AMPR] = evalampr,
	[TOK_CMP] = evalcmp,
	[TOK_HEREDOC] = evalheredoc,
	[TOK_LAMP] = evallamp,
	[TOK_RAMP] = evalramp,
	[TOK_RAOUT] = evalraout,
	[TOK_WORD] = evalword,
	[TOK_DLBRA] = evaltest,
	[TOK_ASSIGN] = evalassign,
	[TOK_LAND] = evaland,
	[TOK_LOR] = evalor,
	['('] = evalsubshell,
	['{'] = evalbracegrp,
	['<'] = evalrin,
	['>'] = evalrout,
	['|'] = evalpipe,
	[';'] = evalsemicolon,
	['&'] = evalampersand,
};

inline void		eval(t_deq *toks, char const *ln)
{
	t_ctx	ctx;
	t_tok	*tok;
	t_job	job;

	ft_bzero(&ctx, sizeof(t_ctx));
	ps_jobctor(ctx.job = &job);
	ctx.ln = ln;
	ctx.stop = toks->len;
	ctx.toks = toks;
	while (ctx.toks->cur < ctx.stop && ctx.toks->cur < ctx.toks->len)
	{
		tok = ft_deqbeg(ctx.toks);
		if (tok->id == TOK_END)
			break ;
		g_eval[tok->id](&ctx, tok);
	}
	ps_jobdtor(ctx.job);
}
