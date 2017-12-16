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

static inline int	lexer_scan_one(t_lexer *self, char peek)
{
	int	st;
	t_tok	t;
	t_tokv	*val;
	t_lrule	*rule;

	FT_INIT(&t, t_tok);
	t.loc = self->src->cur;
	ft_vec_grow(&self->vals, 1);
	val = ft_vec_end(&self->vals);
	FT_INIT(t.val = val, t_tokv);
	rule = (t_lrule *)ft_vec_begin(&self->rules) - 1;
	while (++rule < (t_lrule *)ft_vec_end(&self->rules))
		if ((st = (*rule)(self, &t, peek)) < 0)
			return (st);
		else if (st == 0)
		{
			t.loc.len = (uint16_t)(self->src->cur.cur - t.loc.cur);
			t.val ? ++self->vals.len : 0;
			ft_deq_pushc(&self->toks, &t);
			return (YEP);
		}
		else if ((st = ft_lexer_peek(self, &peek, 0)) || !peek)
			return (st ? st : NOP);
	return (NOP);
}

inline ssize_t		ft_lexer_scan(t_lexer *self, size_t n)
{
	size_t	c;
	char	peek;
	int		st;

	c = 0;
	while (c < n)
		if ((st = ft_lexer_peek(self, &peek, 0)) < 0)
			return (st);
		else if (st || !peek)
			break ;
		else if ((st = lexer_scan_one(self, peek)) < 0)
			return (WUT);
		else if (st == YEP)
			++c;
	return (c);
}

inline ssize_t		ft_lexer_until(t_lexer *self, uint8_t id)
{
	size_t	c;
	char	peek;
	int		st;

	c = 0;
	while (1)
		if ((st = ft_lexer_peek(self, &peek, 0)) < 0)
			return (st);
		else if (st || !peek)
			break ;
		else if ((st = lexer_scan_one(self, peek)) < 0)
			return (WUT);
		else if (st == YEP)
		{
			++c;
			if (!peek || peek == id)
				break ;
		}
	return (c);
}
