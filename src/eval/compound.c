/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/compound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static int	subshell(t_subshell *s)
{
	g_sh->child = 1;
	sh_eval(&s->toks, s->ln);
	return (g_sh->status);
}

static int	bracegrp(t_subshell *s)
{
	sh_eval(&s->toks, s->ln);
	return (g_sh->status);
}

static void	subshelldtor(t_subshell *s)
{
	ft_deqdtor(&s->toks, NULL);
	free(s->ln);
	free(s);
}

inline void	sh_evalsubshell(t_ctx *ctx, t_tok *tok)
{
	int			depth;
	t_subshell	sh;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	ft_bzero(&sh, sizeof(t_subshell));
	ft_deqctor(&sh.toks, sizeof(t_tok));
	depth = 0;
	while ((tok = sh_toknext(ctx->toks))->id != ')' || depth)
	{
		if (tok->id == '(')
			++depth;
		else if (tok->id == ')')
			--depth;
		*(t_tok *)ft_deqpush(&sh.toks) = *tok;
	}
	sh_toknext(ctx->toks);
	(*(t_tok *)ft_deqpush(&sh.toks)).id = TOK_END;
	sh.ln = ft_strdup(ctx->ln);
	ps_procfn(ctx->proc, (t_proccb *)subshell, (t_dtor)subshelldtor,
		ft_memdup(&sh, sizeof(t_subshell)));
	ctx->proc->child = (t_bool)(g_sh->child ? 0 : 1);
}

inline void	sh_evalbracegrp(t_ctx *ctx, t_tok *tok)
{
	int			depth;
	t_subshell	sh;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	ft_bzero(&sh, sizeof(t_subshell));
	ft_deqctor(&sh.toks, sizeof(t_tok));
	depth = 0;
	while ((tok = sh_toknext(ctx->toks))->id != '}' || depth)
	{
		if (tok->id == '{')
			++depth;
		else if (tok->id == '}')
			--depth;
		*(t_tok *)ft_deqpush(&sh.toks) = *tok;
	}
	sh_toknext(ctx->toks);
	(*(t_tok *)ft_deqpush(&sh.toks)).id = TOK_END;
	sh.ln = ft_strdup(ctx->ln);
	ps_procfn(ctx->proc, (t_proccb *)bracegrp, (t_dtor)subshelldtor,
		ft_memdup(&sh, sizeof(t_subshell)));
	ctx->proc->child = 0;
}
