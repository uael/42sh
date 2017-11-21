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

inline void		ft_lexer_ctor(t_lexer *self)
{
	FT_INIT(self, t_lexer);
	ft_vec_ctor(&self->rules, sizeof(t_lrule));
	ft_vec_ctor(&self->srcs, sizeof(t_src));
	ft_vec_ctor(&self->toks, sizeof(t_tok));
	ft_vec_ctor(&self->vals, sizeof(t_tokv));
}

inline t_bool	ft_lexer_init_file(t_lexer *self, char const *filename)
{
	t_src	src;
	t_src	*s;

	ft_lexer_ctor(self);
	ft_src_init_file(&src, filename);
	if (!(s = ft_vec_pushc(&self->srcs, &src)))
		return (0);
	s->cur.src = self->srcs.buf;
	return (1);
}

inline t_bool	ft_lexer_init_str(t_lexer *self, char const *str)
{
	t_src	src;
	t_src	*s;

	ft_lexer_ctor(self);
	ft_src_init_str(&src, str);
	if (!(s = ft_vec_pushc(&self->srcs, &src)))
		return (0);
	s->cur.src = self->srcs.buf;
	return (1);
}

inline t_bool	ft_lexer_init_nstr(t_lexer *self, char const *str, size_t n)
{
	t_src	src;
	t_src	*s;

	ft_lexer_ctor(self);
	ft_src_init_nstr(&src, str, n);
	if (!(s = ft_vec_pushc(&self->srcs, &src)))
		return (0);
	s->cur.src = self->srcs.buf;
	return (1);
}

inline void		ft_lexer_dtor(t_lexer *self)
{
	ft_vec_dtor(&self->rules, NULL);
	ft_vec_dtor(&self->srcs, (void (*)(void *))ft_src_dtor);
	ft_vec_dtor(&self->toks, (void (*)(void *))ft_tokv_dtor);
	ft_vec_dtor(&self->vals, (void (*)(void *))ft_tokv_dtor);
}
