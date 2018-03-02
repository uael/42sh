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

static void		evalif(t_ectx *ctx, t_tok *tok)
{

}

static void		evalwhile(t_ectx *ctx, t_tok *tok)
{

}

static void		evalfuncdef(t_ectx *ctx, t_tok *tok)
{

}

static void		evalsubshell(t_ectx *ctx, t_tok *tok)
{

}

static void		evalbracegrp(t_ectx *ctx, t_tok *tok)
{

}

static void		evalampr(t_ectx *ctx, t_tok *tok)
{

}

static void		evalcmp(t_ectx *ctx, t_tok *tok)
{

}

static void		evalheredoc(t_ectx *ctx, t_tok *tok)
{

}

static void		evallamp(t_ectx *ctx, t_tok *tok)
{

}

static void		evalramp(t_ectx *ctx, t_tok *tok)
{

}

static void		evalraout(t_ectx *ctx, t_tok *tok)
{

}

static void		evalrin(t_ectx *ctx, t_tok *tok)
{

}

static void		evalrout(t_ectx *ctx, t_tok *tok)
{

}

static void		evalword(t_ectx *ctx, t_tok *tok)
{

}

static void		evaltest(t_ectx *ctx, t_tok *tok)
{

}

static void		evalassign(t_ectx *ctx, t_tok *tok)
{

}

inline void		evalpipe(t_ectx *ctx, t_tok *tok)
{

}

inline void		evaland(t_ectx *ctx, t_tok *tok)
{

}

inline void		evalor(t_ectx *ctx, t_tok *tok)
{

}

inline void		evalsemicolon(t_ectx *ctx, t_tok *tok)
{

}

inline void		evalampersand(t_ectx *ctx, t_tok *tok)
{

}

typedef void	(t_evalcb)(t_ectx *ctx, t_tok *tok);

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
	t_ectx	ctx;
	t_tok	*tok;
	t_job	job;

	ft_bzero(&ctx, sizeof(t_ectx));
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
