/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/alias.h"
#include "ush/eval.h"
#include "ush/exp.h"

static void	makebin(t_ctx *ctx, t_tok *tok, t_vec *av)
{
	while (!av->len)
		if (sh_tokis(tok, TOKS_REDIR))
		{
			g_eval[tok->id](ctx, tok);
			tok = sh_tokpeek(ctx->toks);
		}
		else if (sh_tokis(tok, TOKS_WORD))
		{
			sh_expwords(av, ctx->ln + tok->pos, tok->len);
			tok = sh_toknext(ctx->toks);
		}
		else
			break ;
}

inline char	*sh_evalalias(t_ctx *ctx, t_tok *tok, t_vec *av, char const *alias)
{
	t_vec	words;
	char	*cmd;
	int		cmp;

	ft_vecctor(&words, sizeof(char *));
	sh_expwords(&words, alias, ft_strlen(alias));
	cmd = ((char **)av->buf)[0];
	ft_vecsht(av, NULL);
	while (ft_veclen(&words))
	{
		*(char **)ft_vecusht(av) = *(char **)ft_vecback(&words);
		ft_vecpop(&words, NULL);
	}
	if (words.buf)
		free(words.buf);
	makebin(ctx, tok, av);
	if (!av->len)
		return ("true");
	cmp = ft_strcmp(((char **)av->buf)[0], cmd);
	free(cmd);
	return (cmp && (alias = sh_aliasget(((char **)av->buf)[0])) ?
		sh_evalalias(ctx, tok, av, alias) : ((char **)av->buf)[0]);
}
