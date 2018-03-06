/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"
#include "ush/func.h"

static uint8_t	g_end[] = {
	['('] = ')',
	['{'] = '}',
	[TOK_IF] = TOK_FI,
	[TOK_WHILE] = TOK_DONE,
};

static int		avcount(char *av[])
{
	int c;

	c = 0;
	while (*av)
	{
		++av;
		++c;
	}
	return (c);
}

inline int		sh_evalfn(t_proc *proc)
{
	t_func	*fn;
	char	*av0;
	char	*fname;

	av0 = g_sh->av[0];
	if (!sh_scope())
		return (g_sh->status);
	g_sh->av = proc->argv;
	g_sh->ac = avcount(proc->argv);
	g_sh->tty = 0;
	fname = g_sh->av[0];
	if (!(fn = sh_funcget(fname)))
	{
		sh_unscope();
		return (EXIT_FAILURE);
	}
	g_sh->av[0] = av0;
	fn->body.cur = 0;
	sh_eval(&fn->body, fn->ln);
	g_sh->av[0] = fname;
	sh_unscope();
	return (g_sh->status);
}

inline void		sh_evalfuncdef(t_ctx *ctx, t_tok *tok)
{
	t_tok		*beg;
	t_tok		*name;
	t_deq		body;
	char const	*id;
	int			depth;

	depth = 1;
	name = sh_toknext(ctx->toks);
	beg = sh_toknext(ctx->toks);
	ft_deqctor(&body, sizeof(t_tok));
	*(t_tok *)ft_deqpush(&body) = *beg;
	while ((tok = sh_toknext(ctx->toks)))
	{
		*(t_tok *)ft_deqpush(&body) = *tok;
		if (tok->id == beg->id)
			++depth;
		else if (tok->id == g_end[beg->id] && !--depth)
			break ;
	}
	((t_tok *)ft_deqpush(&body))->id = TOK_END;
	sh_toknext(ctx->toks);
	id = ft_strndup(ctx->ln + name->pos, name->len);
	sh_funcset(id, &body, ctx->ln);
	free((void *)id);
}
