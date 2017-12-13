/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer_scan.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/lexer.h"

inline size_t		ft_lexer_clean(t_lexer *self)
{
	return (ft_deq_clean(&self->toks, (t_dtor)ft_tok_dtor));
}

static inline int	lexer_scan_one(t_lexer *self, char peek, t_src *src)
{
	int	st;
	t_tok	t;
	t_tokv	*val;
	t_lrule	*rule;

	FT_INIT(&t, t_tok);
	t.loc = src->cur;
	ft_vec_grow(&self->vals, 1);
	val = ft_vec_end(&self->vals);
	FT_INIT(val, t_tokv);
	t.val = val;
	rule = (t_lrule *)ft_vec_begin(&self->rules) - 1;
	while (++rule < (t_lrule *)ft_vec_end(&self->rules))
		if ((st = (*rule)(&t, peek, src)) < 0)
			return (st);
		else if (st == 0)
		{
			if ((t.loc.len = (uint16_t)(src->cur.cur - t.loc.cur)) && t.val)
				++self->vals.len;
			ft_deq_pushc(&self->toks, &t);
			return (YEP);
		}
		else if ((st = ft_src_peek(src, &peek, 0)) || !peek)
			return (st ? st : NOP);
	return (NOP);
}

inline ssize_t		ft_lexer_scan(t_lexer *self, size_t n)
{
	size_t	c;
	t_src	*src;
	char	peek;
	int		st;

	c = 0;
	while (c < n)
		if (ft_deq_size(&self->srcs) == 0 || !(src = ft_deq_at(&self->srcs, 0)))
			break ;
		else if ((st = ft_src_peek(src, &peek, 0)) < 0)
			return (st);
		else if (st && self->srcs.len > 1)
			ft_deq_shift(&self->srcs, NULL);
		else if (st || !peek)
			break ;
		else if ((st = lexer_scan_one(self, peek, src)) < 0)
			return (WUT);
		else if (st == YEP)
			++c;
	return (c);
}

inline ssize_t		ft_lexer_until(t_lexer *self, uint8_t id)
{
	size_t	c;
	t_src	*src;
	char	peek;
	int		st;

	c = 0;
	while (1)
		if (ft_deq_size(&self->srcs) == 0 || !(src = ft_deq_at(&self->srcs, 0)))
			break ;
		else if ((st = ft_src_peek(src, &peek, 0)) < 0)
			return (st);
		else if (st && self->srcs.len > 1)
			ft_deq_shift(&self->srcs, NULL);
		else if (st || !peek)
			break ;
		else if ((st = lexer_scan_one(self, peek, src)) < 0)
			return (WUT);
		else if (st == YEP)
		{
			++c;
			if (!peek || peek == id)
				break ;
		}
	return (c);
}

inline int			ft_lexer_getc(t_lexer *self, char *c)
{
	t_src	*src;
	ssize_t	sz;

	if (ft_deq_size(&self->srcs) == 0 || !(src = ft_deq_at(&self->srcs, 0)))
		return (NOP);
	if ((sz = ft_src_next(src, c, 1)) < 0)
		return (WUT);
	return (sz == 1 ? YEP : NOP);
}
