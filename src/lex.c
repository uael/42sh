/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 08:03:29 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

inline t_st		sh_lex(t_lexer *self)
{
	t_lrule *it;

	if (!(it = ft_vec_pushn(&self->rules, 2)))
		return (ENO);
	*it = sh_tok_word;
	*(it + 1) = sh_tok_syntax;
	return (OK);
}

inline t_tok	*sh_peek(t_sh *self)
{
	t_tok	*tok;
	t_st	st;

	if (ISE(st = ft_lexer_peek(&self->lexer, 0, &tok)))
		ft_exit(ST_TOENO(st), (t_dtor)sh_dtor, self, "%s: %e\n",
			"msh", ST_TOENO(st));
	return (ST_OK(st) ? tok : NULL);
}

inline t_tok	*sh_peekn(t_sh *self, size_t n)
{
	t_tok	*tok;
	t_st	st;

	if (ISE(st = ft_lexer_peek(&self->lexer, n, &tok)))
		ft_exit(ST_TOENO(st), (t_dtor)sh_dtor, self, "%s: %e\n",
			"msh", ST_TOENO(st));
	return (ST_OK(st) ? tok : NULL);
}

inline t_tok	*sh_next(t_sh *self, t_tok **next)
{
	t_tok	*tok;
	t_sz	sz;

	if (ISE(sz = ft_lexer_next(&self->lexer, 1, &tok)))
		ft_exit((int)ST_TOENO(sz), (t_dtor)sh_dtor, self, "%s: %e\n",
			"msh", ST_TOENO(sz));
	if (next)
		*next = sh_peek(self);
	return (SZ_OK(sz) ? tok : NULL);
}
