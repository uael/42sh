/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer_scan.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/07 12:29:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/lexer.h"

inline size_t		ft_lexer_clean(t_lexer *self)
{
	size_t	n;
	size_t	v;

	n = 0;
	v = 0;
	while (n < self->toks.cur)
		if (((t_tok *)self->toks.buf)[n++].val)
			++v;
	ft_deq_clean(&self->toks, NULL);
	ft_vec_clean(&self->vals, v, (t_dtor)ft_tokv_dtor);
	return (n);
}

static inline t_st	lexer_scan_one(t_lexer *self, char peek, t_src *src)
{
	t_st	st;
	t_tok	t;
	t_tokv	*val;
	t_lrule	*rule;

	FT_INIT(&t, t_tok);
	t.loc = src->cur;
	if (!ft_vec_grow(&self->vals, 1))
		return (ENO);
	val = ft_vec_end(&self->vals);
	FT_INIT(val, t_tokv);
	t.val = val;
	rule = (t_lrule *)ft_vec_begin(&self->rules) - 1;
	while (++rule < (t_lrule *)ft_vec_end(&self->rules))
		if (ISE(st = (*rule)(&t, peek, src)))
			return (st);
		else if (ST_OK(st))
		{
			if ((t.loc.len = (uint16_t)(src->cur.cur - t.loc.cur)) && t.val)
				++self->vals.len;
			return (ft_deq_pushc(&self->toks, &t) ? OK : ENO);
		}
		else if (ST_NOK(st = ft_src_peek(src, &peek, 0)))
			return (st);
	return (NOK);
}

inline t_sz			ft_lexer_scan(t_lexer *self, size_t n)
{
	size_t	c;
	t_src	*src;
	char	peek;
	int		st;

	c = 0;
	while (c < n)
		if (ft_deq_size(&self->srcs) == 0 || !(src = ft_deq_at(&self->srcs, 0)))
			break ;
		else if (ISE(st = ft_src_peek(src, &peek, 0)))
			return (st);
		else if (ST_NOK(st) && self->srcs.len > 1)
			ft_deq_shift(&self->srcs, NULL);
		else if (ST_NOK(st))
			break ;
		else if (ISE(st = lexer_scan_one(self, peek, src)))
			return (ST_TOSZ(st));
		else if (ST_OK(st))
			++c;
	return (c);
}

inline t_sz			ft_lexer_until(t_lexer *self, uint8_t id)
{
	size_t	c;
	t_src	*src;
	char	peek;
	int		st;

	c = 0;
	while (1)
		if (ft_deq_size(&self->srcs) == 0 || !(src = ft_deq_at(&self->srcs, 0)))
			break ;
		else if (ISE(st = ft_src_peek(src, &peek, 0)))
			return (st);
		else if (ST_NOK(st) && self->srcs.len > 1)
			ft_deq_shift(&self->srcs, NULL);
		else if (ST_NOK(st))
			break ;
		else if (ISE(st = lexer_scan_one(self, peek, src)))
			return (ST_TOSZ(st));
		else if (ST_OK(st))
		{
			++c;
			if (!peek || peek == id)
				break ;
		}
	return (c);
}

inline t_st			ft_lexer_getc(t_lexer *self, char *c)
{
	t_src	*src;
	t_sz	sz;

	if (ft_deq_size(&self->srcs) == 0 || !(src = ft_deq_at(&self->srcs, 0)))
		return (NOK);
	if (ISE(sz = ft_src_next(src, c, 1)))
		return (SZ_TOST(sz));
	return (sz == 1 ? OK : NOK);
}
