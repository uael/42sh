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

inline void	sh_evalbang(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	sh_toknext(ctx->toks);
	ctx->job->bang = 1;
}

inline void	sh_evalpipe(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	sh_evalexport(&ctx->vars);
	sh_toknext(ctx->toks);
	ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
	ps_procctor(ctx->proc);
}

inline void	sh_evalpipeand(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	sh_evalexport(&ctx->vars);
	sh_toknext(ctx->toks);
	*(t_redir *)ft_vecpush((t_vec *)&ctx->proc->redirs) = (t_redir){
		0, ft_strdup("1"), STDERR_FILENO, -1, 0, 0
	};
	ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
	ps_procctor(ctx->proc);
}

inline void	sh_evaland(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	sh_evalexport(&ctx->vars);
	sh_toknext(ctx->toks);
	ctx->job->next = ft_malloc(sizeof(t_job));
	ctx->job->andor = ANDOR_AND;
	ps_jobctor(ctx->job->next);
	ctx->job = ctx->job->next;
	ctx->proc = NULL;
}

inline void	sh_evalor(t_ctx *ctx, t_tok *tok)
{
	(void)tok;
	sh_evalexport(&ctx->vars);
	sh_toknext(ctx->toks);
	ctx->job->next = ft_malloc(sizeof(t_job));
	ctx->job->andor = ANDOR_OR;
	ps_jobctor(ctx->job->next);
	ctx->job = ctx->job->next;
	ctx->proc = NULL;
}
