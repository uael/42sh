/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/redir_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"
#include "ush/exp.h"

inline void	sh_evallamp(t_ctx *ctx, t_tok *tok)
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
	kind = 0;
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

inline void	sh_evalramp(t_ctx *ctx, t_tok *tok)
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
	kind = 0;
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

inline void	sh_evalheredoc(t_ctx *ctx, t_tok *tok)
{
	int fd;

	(void)tok;
	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	if (ctx->proc->in)
		free(ctx->proc->in);
	ctx->proc->in = NULL;
	fd = ft_isdigit(*(ctx->ln + tok->pos)) ? *(ctx->ln + tok->pos) - '0' : 0;
	tok = sh_toknext(ctx->toks);
	sh_toknext(ctx->toks);
	if (fd != 0)
		return ;
	ctx->proc->in = ft_strndup(ctx->ln + tok->pos, tok->len);
}

inline void	sh_evalherenow(t_ctx *ctx, t_tok *tok)
{
	int		fd;
	t_sds	word;

	(void)tok;
	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	if (ctx->proc->in)
		free(ctx->proc->in);
	ctx->proc->in = NULL;
	fd = ft_isdigit(*(ctx->ln + tok->pos)) ? *(ctx->ln + tok->pos) - '0' : 0;
	tok = sh_toknext(ctx->toks);
	sh_toknext(ctx->toks);
	if (fd != 0)
		return ;
	ft_sdsctor(&word);
	sh_expword(&word, ctx->ln + tok->pos, tok->len);
	*ft_sdspush(&word) = '\n';
	ctx->proc->in = word.buf;
}

inline void	sh_evalampra(t_ctx *ctx, t_tok *tok)
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
		STDOUT_FILENO, STDERR_FILENO, O_WRONLY | O_CREAT | O_APPEND, 0
	};
	sh_toknext(ctx->toks);
}
