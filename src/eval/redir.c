/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"
#include "ush/exp.h"

inline void	sh_evalampr(t_ctx *ctx, t_tok *tok)
{
	t_sds	file;
	t_tok	*word;
	int		kind;

	(void)tok;
	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	word = sh_toknext(ctx->toks);
	ft_sdsctor(&file);
	kind = 1;
	sh_expword(&file, ctx->ln + word->pos, word->len);
	if (!file.len)
	{
		kind = 2;
		ft_sdsmpush(&file, ctx->ln + word->pos, word->len);
	}
	*(t_redir *)ft_vecpush((t_vec *)&ctx->proc->redirs) = (t_redir){
		kind, file.buf,
		STDOUT_FILENO, STDERR_FILENO, O_WRONLY | O_CREAT | O_TRUNC, 0
	};
	sh_toknext(ctx->toks);
}

inline void	sh_evalcmp(t_ctx *ctx, t_tok *tok)
{
	t_sds	file;
	t_tok	*word;
	int		kind;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	word = sh_toknext(ctx->toks);
	ft_sdsctor(&file);
	kind = 1;
	sh_expword(&file, ctx->ln + word->pos, word->len);
	if (!file.len)
	{
		kind = 2;
		ft_sdsmpush(&file, ctx->ln + word->pos, word->len);
	}
	*(t_redir *)ft_vecpush((t_vec *)&ctx->proc->redirs) = (t_redir){
		kind, file.buf, ft_isdigit(*(ctx->ln + tok->pos))
			? *(ctx->ln + tok->pos) - '0' : STDIN_FILENO, -1,
		O_RDWR | O_CREAT, 0
	};
	sh_toknext(ctx->toks);
}

inline void	sh_evalraout(t_ctx *ctx, t_tok *tok)
{
	t_sds	file;
	t_tok	*word;
	int		kind;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	word = sh_toknext(ctx->toks);
	ft_sdsctor(&file);
	kind = 1;
	sh_expword(&file, ctx->ln + word->pos, word->len);
	if (!file.len)
	{
		kind = 2;
		ft_sdsmpush(&file, ctx->ln + word->pos, word->len);
	}
	*(t_redir *)ft_vecpush((t_vec *)&ctx->proc->redirs) = (t_redir){
		kind, file.buf, ft_isdigit(*(ctx->ln + tok->pos))
			? *(ctx->ln + tok->pos) - '0' : STDOUT_FILENO, -1,
		O_WRONLY | O_CREAT | O_APPEND, 0
	};
	sh_toknext(ctx->toks);
}

inline void	sh_evalrin(t_ctx *ctx, t_tok *tok)
{
	t_sds	file;
	t_tok	*word;
	int		kind;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	word = sh_toknext(ctx->toks);
	ft_sdsctor(&file);
	kind = 1;
	sh_expword(&file, ctx->ln + word->pos, word->len);
	if (!file.len)
	{
		kind = 2;
		ft_sdsmpush(&file, ctx->ln + word->pos, word->len);
	}
	*(t_redir *)ft_vecpush((t_vec *)&ctx->proc->redirs) = (t_redir){
		kind, file.buf, ft_isdigit(*(ctx->ln + tok->pos))
			? *(ctx->ln + tok->pos) - '0' : STDIN_FILENO, -1,
		O_RDONLY, 0
	};
	sh_toknext(ctx->toks);
}

inline void	sh_evalrout(t_ctx *ctx, t_tok *tok)
{
	t_sds	file;
	t_tok	*word;
	int		kind;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	word = sh_toknext(ctx->toks);
	ft_sdsctor(&file);
	kind = 1;
	sh_expword(&file, ctx->ln + word->pos, word->len);
	if (!file.len)
	{
		kind = 2;
		ft_sdsmpush(&file, ctx->ln + word->pos, word->len);
	}
	*(t_redir *)ft_vecpush((t_vec *)&ctx->proc->redirs) = (t_redir){
		kind, file.buf, ft_isdigit(*(ctx->ln + tok->pos))
			? *(ctx->ln + tok->pos) - '0' : STDOUT_FILENO, -1,
		O_WRONLY | O_CREAT | O_TRUNC, 0
	};
	sh_toknext(ctx->toks);
}
