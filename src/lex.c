/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 19:06:49 by alucas-          ###   ########.fr       */
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
		ft_fatal(ST_TOENO(st), (t_dtor)sh_dtor, self, "%s: %e\n",
			"21sh", ST_TOENO(st));
	return (ST_OK(st) ? tok : NULL);
}

inline t_tok	*sh_peekn(t_sh *self, size_t n)
{
	t_tok	*tok;
	t_st	st;

	if (ISE(st = ft_lexer_peek(&self->lexer, n, &tok)))
		ft_fatal(ST_TOENO(st), (t_dtor)sh_dtor, self, "%s: %e\n",
			"21sh", ST_TOENO(st));
	return (ST_OK(st) ? tok : NULL);
}

inline t_tok	*sh_next(t_sh *self, t_tok **next)
{
	t_tok	*tok;
	t_sz	sz;

	if (ISE(sz = ft_lexer_next(&self->lexer, 1, &tok)))
		ft_fatal((int)ST_TOENO(sz), (t_dtor)sh_dtor, self, "%s: %e\n",
			"21sh", ST_TOENO(sz));
	if (next)
		*next = sh_peek(self);
	return (SZ_OK(sz) ? tok : NULL);
}

inline void		sh_consume_line(t_sh *self)
{
	t_tok	*tok;

	while ((tok = sh_peek(self)) && tok->id)
		if ((tok = sh_next(self, NULL)) && tok->id == '\n')
			break ;
}
