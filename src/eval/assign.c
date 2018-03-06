/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/assign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"
#include "ush/exp.h"

static void	assignset(t_ctx *ctx, char *var, char *val)
{
	uint32_t	it;

	if (ft_mapget(&ctx->vars, var, &it))
	{
		free(var);
		free(((char **)ctx->vars.vals)[it]);
		((char **)ctx->vars.vals)[it] = val;
	}
	else if (ft_mapput(&ctx->vars, var, &it))
		((char **)ctx->vars.vals)[it] = val;
	else
	{
		free(var);
		free(val);
	}
}

inline void	sh_evalassign(t_ctx *ctx, t_tok *tok)
{
	char		*eq;
	char		*var;
	t_sds		val;

	if (!ctx->proc)
	{
		ctx->proc = (t_proc *)ft_vecpush((t_vec *)&ctx->job->procs);
		ps_procctor(ctx->proc);
	}
	sh_toknext(ctx->toks);
	eq = ft_strnchr(ctx->ln + tok->pos, '=', tok->len);
	var = ft_strndup(ctx->ln + tok->pos, eq - (ctx->ln + tok->pos));
	ft_sdsctor(&val);
	sh_expword(&val, eq + 1, tok->len - (eq - ctx->ln - tok->pos) - 1);
	!val.len ? (*ft_sdspush(&val) = '\0') : 0;
	ps_procbit(ctx->proc, 0);
	assignset(ctx, var, val.buf);
}

inline void	sh_evalexport(t_map *vars)
{
	uint32_t it;

	if (!vars->len)
		return ;
	it = 0;
	while (it < vars->cap)
	{
		if (!(vars->bucks[it] & BUCKET_BOTH))
		{
			sh_varset(((char **)vars->keys)[it], ((char **)vars->vals)[it]);
			ft_pfree((void **)&((char **)vars->vals)[it]);
			vars->bucks[it] |= BUCKET_DELETED;
			--vars->len;
		}
		++it;
	}
}
