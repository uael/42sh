/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lex/lexer.h"

inline void		ft_lexer_init_stream(t_lexer *self, t_istream *stream)
{
	t_src	src;
	t_src	*s;

	FT_INIT(self, t_lexer);
	ft_vec_ctor(&self->rules, sizeof(t_lrule));
	ft_deq_ctor(&self->srcs, sizeof(t_src));
	ft_deq_ctor(&self->toks, sizeof(t_tok));
	ft_vec_ctor(&self->vals, sizeof(t_tokv));
	ft_src_init_stream(&src, stream);
	s = ft_deq_pushc(&self->srcs, &src);
	s->cur.src = self->srcs.buf;
}

inline int		ft_lexer_init_file(t_lexer *self, char const *filename)
{
	t_src	src;
	t_src	*s;

	FT_INIT(self, t_lexer);
	ft_vec_ctor(&self->rules, sizeof(t_lrule));
	ft_deq_ctor(&self->srcs, sizeof(t_src));
	ft_deq_ctor(&self->toks, sizeof(t_tok));
	ft_vec_ctor(&self->vals, sizeof(t_tokv));
	if (ft_src_init_file(&src, filename) < 0)
		return (WUT);
	s = ft_deq_pushc(&self->srcs, &src);
	s->cur.src = self->srcs.buf;
	return (YEP);
}

inline void		ft_lexer_init_str(t_lexer *self, char const *str)
{
	t_src	src;
	t_src	*s;

	FT_INIT(self, t_lexer);
	ft_vec_ctor(&self->rules, sizeof(t_lrule));
	ft_deq_ctor(&self->srcs, sizeof(t_src));
	ft_deq_ctor(&self->toks, sizeof(t_tok));
	ft_vec_ctor(&self->vals, sizeof(t_tokv));
	ft_src_init_str(&src, str);
	s = ft_deq_pushc(&self->srcs, &src);
	s->cur.src = self->srcs.buf;
}

inline void		ft_lexer_init_nstr(t_lexer *self, char const *str, size_t n)
{
	t_src	src;
	t_src	*s;

	FT_INIT(self, t_lexer);
	ft_vec_ctor(&self->rules, sizeof(t_lrule));
	ft_deq_ctor(&self->srcs, sizeof(t_src));
	ft_deq_ctor(&self->toks, sizeof(t_tok));
	ft_vec_ctor(&self->vals, sizeof(t_tokv));
	ft_src_init_nstr(&src, str, n);
	s = ft_deq_pushc(&self->srcs, &src);
	s->cur.src = self->srcs.buf;
}

inline void		ft_lexer_dtor(t_lexer *self)
{
	ft_vec_dtor(&self->rules, NULL);
	ft_deq_dtor(&self->srcs, (t_dtor)ft_src_dtor);
	ft_deq_dtor(&self->toks, (t_dtor)ft_tokv_dtor);
	ft_vec_dtor(&self->vals, (t_dtor)ft_tokv_dtor);
}
