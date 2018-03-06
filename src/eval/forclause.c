/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/forclause.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"
#include "ush/exp.h"

static int		forclause(t_for *s)
{
	char	*word;
	size_t	i;

	g_sh->child = 1;
	i = 0;
	while (i < s->words.len)
	{
		word = *(char **)ft_vecat(&s->words, i++);
		sh_varset((char *)s->name, word);
		s->body.cur = 0;
		sh_eval(&s->body, s->ln);
	}
	return (g_sh->status = 0);
}

static void		forclausedtor(t_for *s)
{
	ft_vecdtor(&s->words, (t_dtor)ft_pfree);
	ft_deqdtor(&s->body, NULL);
	free((void *)s->name);
	free(s->ln);
	free(s);
}

static t_for	*forclausector(t_ctx *ctx, t_tok *tok, t_tok *name)
{
	t_for forc;

	ft_bzero(&forc, sizeof(t_for));
	ft_vecctor(&forc.words, sizeof(char *));
	while (sh_tokis(tok, TOKS_WORD))
	{
		sh_expwords(&forc.words, ctx->ln + tok->pos, tok->len);
		tok = sh_toknext(ctx->toks);
	}
	sh_toknext(ctx->toks);
	forc.name = ft_strndup(ctx->ln + name->pos, name->len);
	ft_deqctor(&forc.body, sizeof(t_tok));
	sh_pushuntil(&forc.body, ctx->toks, (char[]){TOK_DONE, '\0'},
		(char[]){TOK_DO, TOK_DONE});
	sh_toknext(ctx->toks);
	forc.ln = ft_strdup(ctx->ln);
	return (ft_memdup(&forc, sizeof(t_for)));
}

static void		emptyfor(t_ctx *ctx, t_tok *tok)
{
	int depth;

	ps_procbit(ctx->proc, 0);
	depth = 0;
	while (tok)
	{
		if (tok->id == TOK_DO)
			++depth;
		else if (tok->id == TOK_DONE && !--depth)
			break ;
		tok = sh_toknext(ctx->toks);
	}
	sh_toknext(ctx->toks);
}

inline void		sh_evalfor(t_ctx *ctx, t_tok *tok)
{
	t_tok *name;

	name = sh_toknext(ctx->toks);
	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	if ((tok = sh_toknext(ctx->toks))->id != TOK_IN ||
		!sh_tokis(tok = sh_toknext(ctx->toks), TOKS_WORD))
		return (emptyfor(ctx, tok));
	ps_procfn(ctx->proc, (t_proccb *)forclause, (t_dtor)forclausedtor,
		forclausector(ctx, tok, name));
	ctx->proc->child = (t_bool)(g_sh->child ? 0 : 1);
}
