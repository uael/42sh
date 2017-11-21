/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/lexer.h"

static inline int8_t	lexer_scan_one(t_lexer *self, char peek, t_src *src)
{
	int8_t	r;
	t_tok	tok;
	t_tokv	*val;
	t_lrule	*rule;

	FT_INIT(&tok, t_tok);
	tok.loc = src->cur;
	if (!ft_vec_grow(&self->vals, 1))
		return (-1);
	val = ft_vec_end(&self->vals);
	FT_INIT(val, t_tokv);
	tok.id.val = val;
	rule = (t_lrule *)ft_vec_begin(&self->rules) - 1;
	while (++rule < (t_lrule *)ft_vec_end(&self->rules))
		if ((r = (*rule)(&tok, peek, src)) == -1)
			return (-1);
		else if (r == 0)
		{
			tok.loc.len = (uint16_t)(src->cur.cur - tok.loc.cur);
			if (!tok.is_id)
				++self->vals.len;
			return ((int8_t)(ft_vec_pushc(&self->toks, &tok) ? 0 : -1));
		}
	return (1);
}

inline ssize_t			ft_lexer_scan(t_lexer *self, size_t n)
{
	size_t	c;
	int8_t	r;
	t_src	*src;
	char	peek;

	c = 0;
	while (c < n)
	{
		if (ft_vec_size(&self->srcs) == 0)
			break ;
		src = ft_vec_at(&self->srcs, 0);
		if (!(peek = ft_src_peek(src, 0)))
		{
			ft_vec_shift(&self->srcs, NULL);
			continue ;
		}
		if ((r = lexer_scan_one(self, peek, src)) == -1)
			return (-1);
		if (!r)
			++c;
	}
	return (c);
}
